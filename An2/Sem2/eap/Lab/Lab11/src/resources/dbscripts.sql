CREATE DATABASE `pao_lab_11`;
USE `pao_lab_11`;
SET GLOBAL log_bin_trust_function_creators = 1;

CREATE TABLE `bankaccounts` (
`id` int(11) NOT NULL AUTO_INCREMENT,
`accountNumber` varchar(100) NOT NULL,
`balance` double NOT NULL,
`type` varchar(100) NOT NULL,
`cardNumber` varchar(16) DEFAULT NULL,
PRIMARY KEY (`id`));



DELIMITER $$


CREATE FUNCTION `total_amount_per_type` ( bank_account_type varchar(100))
    RETURNS DOUBLE
BEGIN
	DECLARE total_amount double;
    SELECT sum(balance) INTO total_amount FROM bankaccounts ba WHERE ba.type = bank_account_type;
RETURN total_amount;
END$$

DELIMITER ;