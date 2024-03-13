use ::std::io::Read;
use std::env;
use std::fs::File;
use std::str::Chars;
// https://craftinginterpreters.com/scanning.html
pub const EOF_CHAR: char = '\0';

pub struct Cursor<'a> {
    // len_remaining: usize,
    stream: Chars<'a>,
    line_number: u32,
}

impl<'a> Cursor<'a> {
    pub fn new(input: &'a str) -> Cursor<'a> {
        Cursor {
            // len_remaining: input.len(),
            stream: input.chars(),
            line_number: 1,
        }
    }

    pub fn is_eof(&self) -> bool {
        self.stream.as_str().is_empty()
    }

    pub fn first(&self) -> char {
        self.stream.clone().next().unwrap_or(EOF_CHAR)
    }

    pub fn second(&self) -> char {
        self.stream.clone().nth(1).unwrap_or(EOF_CHAR)
    }

    pub fn next_token(&mut self) -> Token {
        let first_char = self.stream.next().unwrap();
        let mut lexeme = String::from(first_char);
        let token_type = match first_char {
            '\n' => {
                self.line_number += 1;
                TokenKind::Newline
            }

            c if is_whitespace(c) => TokenKind::Whitespace,

            '/' => match self.first() {
                // Line comment
                '/' => {
                    while self.first() != '\n' {
                        lexeme.push(self.stream.next().unwrap())
                    }
                    TokenKind::Comment
                }
                // Block comment
                '*' => {
                    while !(self.first() == '*' && self.second() == '/') {
                        if self.first() == '\n' {
                            self.line_number += 1;
                        }
                        lexeme.push(self.stream.next().unwrap());
                    }
                    lexeme.push(self.stream.next().unwrap());
                    lexeme.push(self.stream.next().unwrap());
                    TokenKind::Comment
                }
                // Division operator
                _ => TokenKind::Operator,
            },

            '"' => {
                while self.first() != '"' {
                    lexeme.push(self.stream.next().unwrap())
                }
                lexeme.push(self.stream.next().unwrap());
                TokenKind::Literal
            }
            '\'' => {
                while self.first() != '\'' {
                    lexeme.push(self.stream.next().unwrap())
                }
                lexeme.push(self.stream.next().unwrap());
                TokenKind::Literal
            }

            // Identifiers or Keywords
            c if c.is_ascii_alphabetic() || c == '_' => {
                while let Some(&c) = self.stream.clone().peekable().peek() {
                    if c.is_ascii_alphanumeric() || c == '_' {
                        lexeme.push(c);
                        self.stream.next();
                    } else {
                        break;
                    }
                }
                match lexeme.as_str() {
                    // List of keywords
                    "fn" | "if" | "else" | "while" | "for" | "match" | "let" | "mut" | "const"
                    | "return" | "u64" | "u32" | "f32" | "i64" | "i32" => TokenKind::Keyword,
                    _ => TokenKind::Identifier,
                }
            }

            // Literals
            c if c.is_ascii_digit() => {
                while let Some(&c) = self.stream.clone().peekable().peek() {
                    if c.is_ascii_digit() || c == '.' {
                        lexeme.push(c);
                        self.stream.next();
                    } else {
                        break;
                    }
                }
                TokenKind::Literal
            }

            // Delimiters
            '(' | ')' | '{' | '}' | '[' | ']' | ';' => TokenKind::Delimiter,

            // Operators
            '+' | '-' | '*' | '%' | '^' | '!' | '&' | '|' | '=' | '>' | '<' | '.' | ':' => {
                let next_char = self.first();
                match (first_char, next_char) {
                    ('=', '=')
                    | ('!', '=')
                    | ('<', '=')
                    | ('>', '=')
                    | ('&', '&')
                    | ('|', '|')
                    | ('>', '>')
                    | ('<', '<')
                    | ('-', '>') => {
                        lexeme.push(next_char);
                        self.stream.next();
                    }
                    _ => {}
                }
                TokenKind::Operator
            }
            // End of File
            _ => TokenKind::EOF,
        };

        Token::new(token_type, lexeme, self.line_number)
    }

    pub fn tokenize(&mut self) -> impl Iterator<Item = Token> {
        let mut tokens = Vec::new();
        while !self.is_eof() {
            let token = self.next_token();
            match token.kind {
                TokenKind::Whitespace | TokenKind::Newline | TokenKind::EOF => {}
                _ => tokens.push(token),
            };
        }
        tokens.into_iter()
    }
}

pub fn is_whitespace(c: char) -> bool {
    matches!(
        c,
        '\u{0009}'   // \t
        // | '\u{000A}' // \n
        | '\u{000B}' // vertical tab
        | '\u{000C}' // form feed
        | '\u{000D}' // \r
        | '\u{0020}' // space
        | '\u{0085}'
        | '\u{200E}' // LEFT-TO-RIGHT MARK
        | '\u{200F}' // RIGHT-TO-LEFT MARK
        | '\u{2028}' // LINE SEPARATOR
        | '\u{2029}' // PARAGRAPH SEPARATOR
    )
}

#[derive(Debug)]
pub struct Token {
    pub lexeme: String,
    pub kind: TokenKind,
    pub line: u32,
}

impl Token {
    fn new(kind: TokenKind, lexeme: String, line: u32) -> Token {
        Token { kind, lexeme, line }
    }
}

impl std::fmt::Display for Token {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "lexeme: {}, kind: {:?}, length: {}, line_number: {}",
            self.lexeme,
            self.kind,
            self.lexeme.len(),
            self.line
        )
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum TokenKind {
    Keyword,
    Identifier,
    Literal,
    Operator,
    Delimiter,
    Comment,
    Whitespace,
    Newline,
    EOF,
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        println!("Usage: {} <path_to_rs_file>", args[0]);
        return;
    }

    let file_path = &args[1];

    if !file_path.ends_with(".rs") {
        println!("Error: Provided file is not a .rs file.");
        return;
    }

    let mut file = match File::open(file_path) {
        Ok(file) => file,
        Err(_) => {
            println!("Error: Unable to open file '{}'", file_path);
            return;
        }
    };

    let mut contents = String::new();
    if file.read_to_string(&mut contents).is_err() {
        println!("Error: Unable to read file '{}'", file_path);
        return;
    }

    let mut cursor = Cursor::new(contents.as_str());

    for token in cursor.tokenize() {
        println!("{}", token);
    }
}
