DROP DATABASE IF EXISTS ctflime;
CREATE DATABASE IF NOT EXISTS ctflime;
use ctflime;

# TARI
##########################################################
-- country tags = ISO 3166-1
-- regions = UN geoscheme
CREATE TABLE tari
	( tara_tag VARCHAR(3) 
    , CONSTRAINT pk_tari PRIMARY KEY(tara_tag)
    , CONSTRAINT chk_tara_tag_lungime CHECK (LENGTH(tara_tag)=3)
    , tara_nume VARCHAR(25) UNIQUE NOT NULL
    , regiune_tag VARCHAR(4) NOT NULL
    );

INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("GER", "Germany", "EUW");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("DEN", "Denmark", "EUW");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("GBR", "United Kingdom", "EUW");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("ROU", "Romania", "EUNE");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("POL", "Poland", "EUNE");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("USA", "United States of America", "NA");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("MEX", "Mexico", "LAN");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("BRA", "Brazil", "LAS");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("AUS", "Australia", "OCE");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("IND", "Indonesia", "SEA");
INSERT INTO tari(tara_tag, tara_nume, regiune_tag) VALUES("TWN", "Taiwan", "SEA");

# ECHIPE
##########################################################
CREATE TABLE echipe
	( echipa_nume VARCHAR(30)
    , CONSTRAINT pk_echipe PRIMARY KEY(echipa_nume)
    , data_creare DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL 
    , echipa_email VARCHAR(40) UNIQUE
    , CONSTRAINT chk_echipa_email_lungime CHECK (LENGTH(echipa_email)>=6)
    , CONSTRAINT regex_echipa_email CHECK(echipa_email REGEXP '^[[:alnum:]._%-\+]+@[[:alnum:].-]+[.][[:alnum:]]{2,4}$')
    , echipa_site VARCHAR(40) UNIQUE
    , join_code VARCHAR(20) UNIQUE NOT NULL
    , academica BOOL DEFAULT FALSE NOT NULL
    , tara_tag VARCHAR(3)
    , CONSTRAINT fk_echipe_tara FOREIGN KEY (tara_tag) REFERENCES tari(tara_tag) ON UPDATE CASCADE ON DELETE SET NULL
    );
    
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, echipa_site, join_code, data_creare) VALUES("dont_thread_on_me",  "dont_thread_on_me@gmail.com", "ROU", "https://github.com/dontthreadonme", "ae3a42fecbd589bfaca9", STR_TO_DATE("2021-06-21 15:02:02", "%Y-%m-%d %H:%i:%s"));
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, echipa_site, join_code, data_creare) VALUES("WreckTheLine",  NULL, "ROU", "https://wrecktheline.com/", "83fb53b35c6fc7f521a0", STR_TO_DATE("2017-03-01 11:42:02", "%Y-%m-%d %H:%i:%s"));
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare) VALUES("tempname",  "tempmail@gmail.com", "ROU", "b1cba2b81a3184f7f19f", STR_TO_DATE("2019-04-19 11:15:47", "%Y-%m-%d %H:%i:%s"));    
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, echipa_site, join_code, data_creare) VALUES("perfectblue",  "perfectblue@gmail.com", "USA", "https://perfect.blue/", "3a7b2f8b1ccec2a1b669", STR_TO_DATE("2009-05-20 11:15:47", "%Y-%m-%d %H:%i:%s"));
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare) VALUES("ALLES",  "allesctfteam@gmail.com", NULL, "a0c7357c922799c1fb60", STR_TO_DATE("2012-03-14 06:05:34", "%Y-%m-%d %H:%i:%s"));    
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare) VALUES("Balsn",  NULL, "TWN", "d9e08675b962ed932f37", STR_TO_DATE("2015-11-20 16:49:47", "%Y-%m-%d %H:%i:%s"));
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, academica) VALUES("hxp",  NULL, NULL, "f31849d2057f54cef74c", FALSE);
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare) VALUES("Katzebin", "Katzebin@yahoo.com", NULL, "a189140493746049d505", STR_TO_DATE("2013-08-15 05:31:48", "%Y-%m-%d %H:%i:%s"));      
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare) VALUES("DiceGang", "DiceGang@hotmail.co.uk", NULL, "5d00a4bb2293254c054b", STR_TO_DATE("2010-06-17 13:34:13", "%Y-%m-%d %H:%i:%s"));  
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare) VALUES("PlaidParliamentofPwning", "PlaidParliamentofPwning@yahoo.com", "DEN", "73bb7cdc17bfbfa68b9b", STR_TO_DATE("2010-12-21 20:28:51", "%Y-%m-%d %H:%i:%s"));
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare) VALUES("pasten", "pasten@gmail.com", "DEN", "1088c3f92967e8253a65", STR_TO_DATE("2017-01-25 16:34:53", "%Y-%m-%d %H:%i:%s"));
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare, academica) VALUES("pwnibuc", "pwnibuc@yahoo.com", "ROU", "a4ae09ae882510bc242e", STR_TO_DATE("2019-11-05 09:59:15", "%Y-%m-%d %H:%i:%s"), TRUE);
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare, academica) VALUES("SuperGuesser", "SuperGuesser@gmail.com", "GER", "56f894cc388557724ac9", STR_TO_DATE("2018-06-16 03:18:08", "%Y-%m-%d %H:%i:%s"), TRUE);
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare) VALUES("MoreSmokedLeetChicken", "MoreSmokedLeetChicken@gmail.com", "IND", "b8be5bafc3fcd585f107", STR_TO_DATE("2016-11-08 00:12:32", "%Y-%m-%d %H:%i:%s"));
INSERT INTO echipe(echipa_nume, echipa_email, tara_tag, join_code, data_creare) VALUES("TeaDeliverers", "TeaDeliverers@yahoo.com", NULL, "6edbd1b7218a1497c2aa", STR_TO_DATE("2018-05-29 01:06:07", "%Y-%m-%d %H:%i:%s"));

# UTILIZATORI
##########################################################
CREATE TABLE utilizatori
	( user_nume VARCHAR(25)
    , CONSTRAINT pk_utilizatori PRIMARY KEY(user_nume)
    , CONSTRAINT chk_user_nume_lungime CHECK (LENGTH(user_nume)>=3)
    , user_email VARCHAR(40) UNIQUE NOT NULL
    , CONSTRAINT chk_user_email_lungime CHECK (LENGTH(user_email)>=6)
	, CONSTRAINT regex_user_email CHECK(user_email REGEXP '^[[:alnum:]._%-\+]+@[[:alnum:].-]+[.][[:alnum:]]{2,4}$')
    , user_parola VARCHAR(40) NOT NULL
    , CONSTRAINT chk_user_parola_lungime  CHECK(LENGTH(user_parola)>=8)
    , data_creare DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL
    , echipa_nume VARCHAR(30)
    , CONSTRAINT fk_utilizatori_echipa FOREIGN KEY (echipa_nume) REFERENCES echipe(echipa_nume) ON UPDATE CASCADE ON DELETE SET NULL
    );

INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("leaK.u", "licu.mihai21@gmail.com", "dont_thread_on_me", "03BFqrnPXi", STR_TO_DATE("2021-6-01 13:55:02", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("binarysheep", "cristiansimache@gmail.com", "dont_thread_on_me", "zRnqjDUS1C", STR_TO_DATE("2021-6-01 11:23:45", "%Y-%m-%d %H:%i:%s")); 
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("Volrin", "maresm@gmail.com", "dont_thread_on_me", "iCvj7D1RdN", STR_TO_DATE("2021-6-15 17:53:54", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("liveoverflow", "liveoverflow@gmail.com", "ALLES", "mx3Dn0kqBj", STR_TO_DATE("2008-12-20 13:51:54", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("connon", "connon@gmail.com", "Katzebin", "LHVXbAr0cQ", STR_TO_DATE("2013-03-04 21:58:55", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("sonigh", "sonigh@yahoo.com", "hxp", "tpBjHG1eio", STR_TO_DATE("2014-09-10 19:24:40", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("entowned", "entowned@hotmail.co.uk", "PlaidParliamentofPwning", "uxHVqgvIsj", STR_TO_DATE("2017-02-01 17:48:33", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("owlinegue", "owlinegue@yahoo.com", NULL, "2utwYisKec", STR_TO_DATE("2018-03-12 20:47:06", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("elylaim", "elylaim@yahoo.com", NULL, "JuaMr5UTgX", STR_TO_DATE("2016-06-25 05:32:57", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("mitlist", "mitlist@gmail.com", "MoreSmokedLeetChicken", "1TIut0zbYV", STR_TO_DATE("2017-12-15 02:03:59", "%Y-%m-%d %H:%i:%s"));        
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("kening", "kening@hotmail.co.uk", "perfectblue", "phzTdt7SkL", STR_TO_DATE("2016-04-10 19:28:34", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("nsiveding", "nsiveding@gmail.com", "pasten", "NfqvtOAQd8", STR_TO_DATE("2017-06-24 08:37:25", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("harrominen", "harrominen@gmail.com", NULL, "J0wpqixMO2", STR_TO_DATE("2011-09-19 18:26:45", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("tivesuc", "tivesuc@hotmail.co.uk", "DiceGang", "q849tUYS1Q", STR_TO_DATE("2014-05-07 20:21:41", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("udoaffe", "udoaffe@hotmail.co.uk", NULL, "1XYaqV35xf", STR_TO_DATE("2018-02-22 14:50:22", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("ssingstr", "ssingstr@yahoo.com", "perfectblue", "Io3GJ2BjaQ", STR_TO_DATE("2010-05-05 07:37:40", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("whzen", "whzen@hotmail.co.uk", "ALLES", "uq24cZ9G5N", STR_TO_DATE("2009-06-24 10:14:33", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("ondlant", "ondlant@yahoo.com", "Balsn", "fmJOYFhkC3", STR_TO_DATE("2008-09-29 06:15:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO utilizatori(user_nume, user_email, echipa_nume, user_parola, data_creare) VALUES("gatewaboo", "gatewaboo@yahoo.com", "Katzebin", "2qc6wE1afo", STR_TO_DATE("2010-01-03 03:26:56", "%Y-%m-%d %H:%i:%s"));

# AUTORI
##########################################################
CREATE TABLE autori
	( autor_nume VARCHAR(25)
    , CONSTRAINT pk_autori PRIMARY KEY(autor_nume)
    , CONSTRAINT chk_autor_nume_lungime CHECK (LENGTH(autor_nume)>=3)
    , autor_email VARCHAR(40) UNIQUE NOT NULL
    , CONSTRAINT chk_autor_email_lungime CHECK (LENGTH(autor_email)>=6)
	, CONSTRAINT regex_autor_email CHECK(autor_email REGEXP '^[[:alnum:]._%-\+]+@[[:alnum:].-]+[.][[:alnum:]]{2,4}$')
	, companie VARCHAR(20)
    );
    
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("volf", "volf@gmail.com", NULL);
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("Ephvuln", "Ephvuln@gmail.com", NULL);
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("yakuhito", "yakuh@gmail.com", NULL);
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("nytr0gen", "nitrogen@yahoo.com", "Bitdefender");
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("trollzorftw", "trollzor@yahoo.com", NULL);
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("albertVartic", "avartic@yahoo.com", "Petrom");
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("rdeaconescu", "rdeaconescueaconescu@yahoo.com", "UPB");
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("Betaflash", "alphabetaflash@gmail.com", NULL);
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("ZNQ", "zenequ@gmail.com", NULL);
INSERT INTO autori(autor_nume, autor_email, companie) VALUES("shad", "shad@hotmail.com", NULL);

# CONCURSURI_CTF
##########################################################
CREATE TABLE concursuri_ctf
	( concurs_id DECIMAL(4)
    , CONSTRAINT pk_concursuri PRIMARY KEY(concurs_id)
    , CONSTRAINT chk_id_concurs_pozitiv CHECK (concurs_id >= 0)
    , concurs_nume VARCHAR(20) NOT NULL
    , concurs_editie DECIMAL(3) NOT NULL
    , CONSTRAINT chk_editie_concurs_strictpozitiv CHECK (concurs_editie > 0)
    , CONSTRAINT uq_nume_editie UNIQUE(concurs_nume, concurs_editie)
    , timp_inceput DATETIME NOT NULL
    , timp_terminat DATETIME NOT NULL
    , CONSTRAINT chk_terminat_dupa_inceput CHECK (timp_terminat > timp_inceput)
    );

INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(0, "Unbreakable", 1, STR_TO_DATE("2019-03-06 12:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2019-03-09 12:00:00", "%Y-%m-%d %H:%i:%s"));
INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(1, "Google CTF", 1, STR_TO_DATE("2019-06-08 13:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2019-06-10 13:00:00", "%Y-%m-%d %H:%i:%s"));
INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(2, "Unbreakable", 2, STR_TO_DATE("2019-10-20 12:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2019-10-23 12:00:00", "%Y-%m-%d %H:%i:%s"));
INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(3, "HackTheBox", 1, STR_TO_DATE("2021-02-20 15:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2021-02-22 15:00:00", "%Y-%m-%d %H:%i:%s"));
INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(4, "RedPWN", 1, STR_TO_DATE("2021-06-01 07:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2021-06-07 07:00:00", "%Y-%m-%d %H:%i:%s"));
INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(5, "ROCSC", 1, STR_TO_DATE("2020-07-10 16:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2020-07-12 16:00:00", "%Y-%m-%d %H:%i:%s"));
INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(6, "GoogleCTF", 2, STR_TO_DATE("2020-07-10 18:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2020-07-11 18:00:00", "%Y-%m-%d %H:%i:%s"));
INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(7, "Unbreakable", 3, STR_TO_DATE("2020-03-08 12:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2020-03-11 12:00:00", "%Y-%m-%d %H:%i:%s"));
INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(8, "DownUnderCTF", 1, STR_TO_DATE("2022-03-06 03:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2022-03-10 03:00:00", "%Y-%m-%d %H:%i:%s"));
INSERT INTO concursuri_ctf(concurs_id, concurs_nume, concurs_editie, timp_inceput, timp_terminat) VALUES(9, "Unbreakable", 4, STR_TO_DATE("2020-10-26 12:00:00", "%Y-%m-%d %H:%i:%s"), STR_TO_DATE("2020-10-29 12:00:00", "%Y-%m-%d %H:%i:%s"));

# PROBLEME
##########################################################
CREATE TABLE probleme
	( problema_id DECIMAL(4)
    , CONSTRAINT pk_probleme PRIMARY KEY(problema_id)
    , CONSTRAINT chk_id_problema_pozitiv CHECK (problema_id >= 0)
    , problema_nume VARCHAR(20) NOT NULL
    , categorie VARCHAR(10) NOT NULL
    , flag VARCHAR(280) NOT NULL
    , puncte DECIMAL(4) NOT NULL
    , CONSTRAINT chk_pct_strictpozitive CHECK(puncte >= 0)
    , arhiva VARCHAR(20) NOT NULL
    , autor VARCHAR(25) NOT NULL
    , CONSTRAINT fk_probleme_autor FOREIGN KEY (autor) REFERENCES autori(autor_nume) ON UPDATE CASCADE ON DELETE CASCADE
    , concurs_id DECIMAL(4) NOT NULL
    , CONSTRAINT fk_probleme_concurs FOREIGN KEY (concurs_id) REFERENCES concursuri_ctf(concurs_id) ON UPDATE CASCADE ON DELETE CASCADE
    , CONSTRAINT uq_concurs_numeprob UNIQUE(concurs_id, problema_nume)
    , CONSTRAINT uq_concurs_arhiva UNIQUE(concurs_id, arhiva)
    , CONSTRAINT uq_numeprob_autor UNIQUE (problema_nume, autor)
    );
    

INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(0, 0, "volf", "crypto", "AESbreak", 500, "CTF{F393AAB2A1C956283A3491EAE53C2875B44B60149A25CD37271102405DB80B00}", "chall.7z");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(1, 5, "shad", "crypto", "TWOringMachine", 500, "CTF{84EBFDFFF45D2DDECB583FFB74E51FDF3F124EC7F0A4D9D7FB2F9EF01B068F31}", "chall.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(2, 5, "shad", "web", "xsselsior", 100, "CTF{DF38371D3332DAFA30B8EEAEEF67F926168FEA403743F0810186E31925A2376A}", "description.rar");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(3, 1, "shad", "rev", "bufferoverflowie", 250, "CTF{62360ED6B531B48B60B64FF95A00FDE95FC13E62B60ADF3B69BE899B1BB93B72}", "bufferoverflowie.tar");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(4, 4, "Betaflash", "pwn", "backd00r", 1000, "CTF{B947106A08AF2799D09FB9D6A187B7C0CB2E66A3E408E754296D76A62592957A}", "pwnexploit.tar");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(5, 4, "rdeaconescu", "crypto", "mexicanradio", 500, "CTF{9A55314E69A01EB595DBA901C439D834362F31C5057091456A8BD179FFF3EF4E}", "dondeesta.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(6, 5, "Ephvuln", "forensics", "investigator",  250, "CTF{AB733CB605119DCD723F6CE9FDE253DA226AE72E743B323029398080B63FE60D}", "privateeye.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(7, 3, "Betaflash", "crypto", "lost_message_v2",  250, "CTF{C7055C63375FE984DABB5CB628EE9CDED185C98D37A29019E30247F65117F71E}", "message.7z");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(8, 1, "rdeaconescu", "forensics", "yellow-duck",  100, "CTF{DD46B5592F4D3CA577E092E882855C04E5A64ABF2A5355CFC1912FE282E05DA7}","volatility-dump.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(9, 4, "nytr0gen", "rev", "babyrop",  100, "CTF{84D4F81C33FD56EA63815C31F7DFBC28C8566757DF9792D6D2E3BF2FD8D5D0C5}", "babyrop.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(10, 0, "volf", "algo", "reverselinkedlist",  1000, "CTF{DCD5FC6B90E43EBFB00279D09C6A1C0F42302668D674F1A8A81A29D1941C8C0E}", "algoprob.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(11, 4, "ZNQ", "misc", "russiandoll",  500, "CTF{C919C51BDB9494362840C9EF8102C23B22993C908EF7C8A6CD451317E052FEA6}", "chall.7z");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(12, 5, "shad", "misc", "alien-console",  100, "CTF{41C706F926890A082D5FD63CD8A1BC8133BF28079C3F4A771594F4F285311258}", "alienconsole.rar");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(13, 4, "nytr0gen", "pwn", "bluebird", 100, "CTF{0A4F33CC9A744909BB4154E0C4FDCC34B9B5C2185AC67F7EBE45DC64DBE7C9A1}","birdpwn.tar");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(14, 5, "ZNQ", "algo", "DJikstra",  250, "CTF{399E20A69A54B94A5AA03F06341FE3275EAF5B03A84E601837A74585B1800974}", "algochall.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(15, 9, "rdeaconescu", "forensics", "volatile", 500, "CTF{84FE9B3DB7649546AFAE7B0EA3FF4430104A1184E8BACFD3936300A9961BA9E7}", "volatility-dump.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(16, 3, "Ephvuln", "crypto", "romaneseuntdomus", 1000, "CTF{7CD76792FABD1F9A74F7700CB7D60436A8A8C6BEE9B3BF885C7C3BE158C64FBC}","cypher.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(17, 0, "albertVartic", "pwn", "backd00r", 500, "CTF{D47473368439D8D50418399847AC2433B24DB4310AF4D0838DE252F625751523}","backd004.tar");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(18, 0, "trollzorftw", "misc", "russiandoll", 500, "CTF{9EE8CE338B6A9F4214435299DE7F10241C69D8D51CE258CA2489E9A465C0F14D}","russiandoll.zip");
INSERT INTO probleme(problema_id, concurs_id, autor, categorie, problema_nume, puncte, flag, arhiva) VALUES(19, 1, "ZNQ", "forensics", "eyewitness", 1000, "CTF{04B0C74F9445D22DAA565B5877FBAC01251C787E5B5F7C981DB2B9AADCDD61BE}","iwitness.rar");

# REZOLVARI
##########################################################
CREATE TABLE rezolvari (
    rezolvare_id DECIMAL(5),
    CONSTRAINT pk_rezolvari PRIMARY KEY (rezolvare_id),
    CONSTRAINT chk_id_rezolvare_pozitiv CHECK (rezolvare_id >= 0),
    rezolvare_descriere VARCHAR(35) NOT NULL,
    CONSTRAINT chk_nume_descriere_lungime CHECK (LENGTH(rezolvare_descriere) >= 6),
    oficiala BOOL NOT NULL DEFAULT FALSE,
    nota DECIMAL(4 , 2 ),
    CONSTRAINT chk_nota_posibila CHECK (nota BETWEEN 0 AND 10),
    problema_id DECIMAL(4) NOT NULL,
    CONSTRAINT fk_rezolvari_problema_id FOREIGN KEY (problema_id)
        REFERENCES probleme (problema_id)
        ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT uq_nume_perproblema UNIQUE (rezolvare_descriere , problema_id)
);

INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(0, 1, TRUE, 10, "aesguide.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(1, 1, FALSE, 7.30, "exploit.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(2, 4, FALSE, 8.10, "reverseshell.pdf");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(3, 6, FALSE, 9.30, "volatilityguide.pdf");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(4, 11, FALSE, 10, "unzipspam.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(5, 1, FALSE, 8.95, "shortsolve.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(6, 13, TRUE, 9.38, "canarybypass.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(7, 6, FALSE, 9.39, "volatilememorydump.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(8, 8, FALSE, 9, "investigatorWriteup.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(9, 2, TRUE, 9.55, "xsswalkthrough.pdf");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(10, 5, TRUE, 7.99, "indentifiedcipher.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(11, 1, FALSE, 3.50, "writeupquiz.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(12, 3, FALSE, 7.50, "begginerbof.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(13, 7, FALSE, 8.35, "decryptmessage.txt");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(14, 14, TRUE, 9.30, "djikstrapreprocessing.pdf");
INSERT INTO rezolvari(rezolvare_id, problema_id, oficiala, nota, rezolvare_descriere) VALUES(15, 19, FALSE, 6.90, "dictionaryapproach.txt");

# SERVERE
##########################################################
CREATE TABLE servere
	( ip VARCHAR(15) 
	, CONSTRAINT chk_ip_lungime CHECK (LENGTH(ip)>=7)
    , adresa_port DECIMAL(5)
    , CONSTRAINT chk_port_range_valid CHECK(adresa_port BETWEEN 1 AND 65535)
    , CONSTRAINT pk_servere PRIMARY KEY (ip, adresa_port)
    , problema_id DECIMAL(4)
    , CONSTRAINT fk_servere_problema FOREIGN KEY (problema_id) REFERENCES probleme(problema_id) ON UPDATE CASCADE ON DELETE SET NULL
    );
    
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("193.163.64.30", 7659, 1);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("1.155.113.185", 3717, 3);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("176.178.95.130", 5035, 5);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("71.150.135.237", 57941, 1);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("217.182.23.166", 35540, 6);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("164.164.15.93", 28494, 1);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("164.164.15.93", 5035, 5);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("193.163.64.30", 14698, 8);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("217.182.23.166", 34013, 11);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("164.164.15.93", 47282, 12);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("193.163.64.30", 23459, 17);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("131.31.110.241", 64858, 19);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("193.163.64.30", 1991, 13);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("96.215.161.177", 61832, 6);
INSERT INTO servere(ip, adresa_port, problema_id) VALUES("176.178.95.130", 45087, NULL);

# TABEL ASOCIATIV INCERCARI
##########################################################
CREATE TABLE incercari
	( incercare_id DECIMAL(6)
    , CONSTRAINT pk_incercari PRIMARY KEY(incercare_id)
    , CONSTRAINT chk_id_incercare_pozitiv CHECK (incercare_id >= 0)
    , problema_id DECIMAL(4) NOT NULL
    , CONSTRAINT fk_incercari_problema_id FOREIGN KEY (problema_id) REFERENCES probleme(problema_id) ON UPDATE CASCADE ON DELETE CASCADE
    , echipa_nume VARCHAR(30) NOT NULL
    , CONSTRAINT fk_incercari_echipa_nume FOREIGN KEY (echipa_nume) REFERENCES echipe(echipa_nume) ON UPDATE CASCADE ON DELETE CASCADE
    , incercare_flag VARCHAR(280) NOT NULL
    , incercare_timp DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL
    , CONSTRAINT uq_prob_echipa_timp UNIQUE(problema_id, echipa_nume, incercare_timp)
	);
    
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(0, 11, "perfectblue", "CTF{C919C51BDB9494362840C9EF8102C23B22993C908EF7C8A6CD451317E052FEA6}", STR_TO_DATE("2020-03-09 05:29:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(1, 15, "ALLES", "CTF{84FE9B3DB7649546AFAE7B0EA3FF4430104A1184E8BACFD3936300A9961BA9E7}", STR_TO_DATE("2020-10-27 07:23:57", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(2, 18, "Katzebin", "CTF{C7055C63375FE984DABB5CB628EE9CDED185C98D37A29019E30247F65117F71E}", STR_TO_DATE("2019-07-10 15:29:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(3, 1, "Katzebin", "CTF{84D4F81C33FD56EA63815C31F7DFBC28C8566757DF9792D6D2E3BF2FD8D5D0C5}", STR_TO_DATE("2020-07-11 08:30:27", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(4, 8, "tempname", "testflag", STR_TO_DATE("2013-03-06 15:29:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(5, 3, "dont_thread_on_me", "CTF{62360ED6B531B48B60B64FF95A00FDE95FC13E62B60ADF3B69BE899B1BB93B72}", STR_TO_DATE("2019-06-09 15:23:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(6, 5, "DiceGang", "CTF{9A55314E69A01EB595DBA901C439D834362F31C5057091456A8BD179FFF3EF4E}", STR_TO_DATE("2021-06-01 03:32:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(7, 19, "pwnibuc", "CTF{c6b312868e056101fe03dcb5c90a3b317993bf99ee23384719be0016c4acd149}", STR_TO_DATE("2019-06-09 10:33:29", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(8, 19, "pwnibuc", "CTF{b52b83c8cd7e650712e3204d1767e5a71232965285796172c09f3d70ee8256b5}", STR_TO_DATE("2019-06-09 11:30:10", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(9, 19, "pwnibuc", "CTF{04B0C74F9445D22DAA565B5877FBAC01251C787E5B5F7C981DB2B9AADCDD61BE}", STR_TO_DATE("2019-06-09 11:40:44", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(10, 1, "pasten", "CTF{9A55314E69A01EB595DBA901C439D834362F31C5057091456A8BD179FFF3EF4E}", STR_TO_DATE("2020-07-10 07:29:31", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(11, 7, "dont_thread_on_me", "CTF{C7055C63375FE984DABB5CB628EE9CDED185C98D37A29019E30247F65117F71E}", STR_TO_DATE("2021-03-21 05:29:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(12, 11, "dont_thread_on_me", "CTF{C919C51BDB9494362840C9EF8102C23B22993C908EF7C8A6CD451317E052FEA6}", STR_TO_DATE("2020-03-09 08:39:17", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(13, 12, "WreckTheLine", "CTF{41C706F926890A082D5FD63CD8A1BC8133BF28079C3F4A771594F4F285311258}", STR_TO_DATE("2020-09-11 05:29:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(14, 15, "DiceGang", "CTF{62360ED6B531B48B60B64FF95A00FDE95FC13E62B60ADF3B69BE899B1BB93B72}", STR_TO_DATE("2020-10-27 05:29:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(15, 13, "hxp", "CTF{ddbabe239a6e990a53c95c9a7932313d3125de738537aba9ddb6ac5cfc6f3eff}", STR_TO_DATE("2013-03-06 05:29:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(16, 8, "MoreSmokedLeetChicken", "CTF{DD46B5592F4D3CA577E092E882855C04E5A64ABF2A5355CFC1912FE282E05DA7}", STR_TO_DATE("2019-06-09 07:39:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(17, 8, "perfectblue", "CTF{BB46B5592F4D3CA577E092E882855C04E5A64ABF2A5355CFC1912FE282E05DA7}", STR_TO_DATE("2019-06-09 06:21:52", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(18, 17, "pasten", "CTF{D47473368439D8D50418399847AC2433B24DB4310AF4D0838DE252F625751523}", STR_TO_DATE("2019-03-08 05:29:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(19, 3, "PlaidParliamentofPwning", "CTF{62360ED6B531B48B60B64FF95A00FDE95FC13E62B60ADF3B69BE899B1BB93B72}", STR_TO_DATE("2019-06-10 11:29:37", "%Y-%m-%d %H:%i:%s"));
INSERT INTO incercari(incercare_id, problema_id, echipa_nume, incercare_flag, incercare_timp) VALUES(20, 9, "WreckTheLine", "CTF{84D4F81C33FD56EA63815C31F7DFBC28C8566757DF9792D6D2E3BF2FD8D5D0C5}", STR_TO_DATE("2019-06-09 09:29:31", "%Y-%m-%d %H:%i:%s"));


COMMIT;