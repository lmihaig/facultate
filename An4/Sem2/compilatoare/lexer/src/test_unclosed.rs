fn fibonacci(n: u64) -> u64 {
    if n == 0 {
        return 0;
    } else if n == 1 {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}


/* this is an unclosed block comment
* and it will throw an error /

fn main() {
    let limit = 10;
    println!("Fibonacci series up to {}: ", limit);
    for i in 0..limit {
        println!("{}", fibonacci(i));
    }
}

