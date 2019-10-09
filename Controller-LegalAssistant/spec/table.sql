CREATE TABLE `address` (
  `id` int(11) DEFAULT NULL,
  `name` text,
  `address` text,
  `create_date` datetime DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `boss` (
  `id` int(11) DEFAULT NULL,
  `name` text,
  `boss` text,
  `create_date` datetime DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `establish` (
  `id` int(11) DEFAULT NULL,
  `creator` text,
  `year` int(11) DEFAULT NULL,
  `place` text,
  `service` text,
  `create_date` datetime DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `fuzzyWord` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `fuzzyWord` varchar(32) NOT NULL,
  `correctWord` varchar(32) DEFAULT NULL,
  `create_date` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `fuzzyWord_UNIQUE` (`fuzzyWord`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8;

CREATE TABLE `intent` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `keyword` text NOT NULL,
  `intent` int(11) NOT NULL,
  `table_name` varchar(45) NOT NULL,
  `create_date` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;

CREATE TABLE `investment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `keyword` text,
  `intent` int(11) NOT NULL,
  `table_name` varchar(45) NOT NULL,
  `create_date` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

CREATE TABLE `payment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `keyword` text NOT NULL,
  `intent` int(11) NOT NULL,
  `table_name` varchar(45) NOT NULL,
  `create_date` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

CREATE TABLE `sandbox` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `keyword` text NOT NULL,
  `intent` int(11) NOT NULL,
  `table_name` varchar(45) NOT NULL,
  `create_date` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

CREATE TABLE `startup` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `keyword` text NOT NULL,
  `intent` int(11) NOT NULL,
  `table_name` varchar(45) NOT NULL,
  `create_date` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
