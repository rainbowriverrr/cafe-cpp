INSERT INTO MenuItem VALUES ("Undefined Symbol",2.29, "Blonde Roast");
INSERT INTO MenuItem VALUES ("Memory Leak",3.00, "Medium Roast");
INSERT INTO MenuItem VALUES ("Segmentation Fault",3.00, "Dark Roast");
INSERT INTO MenuItem VALUES ("GNUppuccino",3.49, "Cappuccino");
INSERT INTO MenuItem VALUES ("Stack Overflow",10.49, "Big Fat Hamburger");

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-10 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-10 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-10 days'),1);

INSERT INTO OrderDetail VALUES (NULL,1,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,1,'Latte',20);
INSERT INTO OrderDetail VALUES (NULL,2,'Coffee',30);
INSERT INTO OrderDetail VALUES (NULL,3,'Coffee',30);
INSERT INTO OrderDetail VALUES (NULL,3,'Cookie',42);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-9 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-9 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-9 days'),1);

INSERT INTO OrderDetail VALUES (NULL,4,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,4,'Latte',30);
INSERT INTO OrderDetail VALUES (NULL,5,'Coffee',30);
INSERT INTO OrderDetail VALUES (NULL,6,'Coffee',10);
INSERT INTO OrderDetail VALUES (NULL,6,'Cookie',26);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-8 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-8 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-8 days'),1);

INSERT INTO OrderDetail VALUES (NULL,7,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,7,'Latte',10);
INSERT INTO OrderDetail VALUES (NULL,8,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,9,'Coffee',60);
INSERT INTO OrderDetail VALUES (NULL,9,'Cookie',30);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-7 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-7 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-7 days'),1);

INSERT INTO OrderDetail VALUES (NULL,10,'Coffee',30);
INSERT INTO OrderDetail VALUES (NULL,10,'Latte',10);
INSERT INTO OrderDetail VALUES (NULL,11,'Coffee',10);
INSERT INTO OrderDetail VALUES (NULL,12,'Coffee',50);
INSERT INTO OrderDetail VALUES (NULL,12,'Cookie',30);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-6 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-6 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-6 days'),1);

INSERT INTO OrderDetail VALUES (NULL,13,'Coffee',30);
INSERT INTO OrderDetail VALUES (NULL,13,'Latte',30);
INSERT INTO OrderDetail VALUES (NULL,14,'Coffee',30);
INSERT INTO OrderDetail VALUES (NULL,15,'Coffee',30);
INSERT INTO OrderDetail VALUES (NULL,15,'Cookie',35);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-5 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-5 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-5 days'),1);

INSERT INTO OrderDetail VALUES (NULL,16,'Coffee',10);
INSERT INTO OrderDetail VALUES (NULL,16,'Latte',20);
INSERT INTO OrderDetail VALUES (NULL,17,'Coffee',40);
INSERT INTO OrderDetail VALUES (NULL,18,'Coffee',10);
INSERT INTO OrderDetail VALUES (NULL,18,'Cookie',30);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-4 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-4 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-4 days'),1);

INSERT INTO OrderDetail VALUES (NULL,19,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,19,'Latte',40);
INSERT INTO OrderDetail VALUES (NULL,20,'Coffee',10);
INSERT INTO OrderDetail VALUES (NULL,21,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,21,'Cookie',18);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-3 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-3 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-3 days'),1);

INSERT INTO OrderDetail VALUES (NULL,22,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,22,'Latte',10);
INSERT INTO OrderDetail VALUES (NULL,23,'Coffee',40);
INSERT INTO OrderDetail VALUES (NULL,24,'Coffee',30);
INSERT INTO OrderDetail VALUES (NULL,24,'Cookie',30);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-2 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-2 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-2 days'),1);

INSERT INTO OrderDetail VALUES (NULL,25,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,25,'Latte',20);
INSERT INTO OrderDetail VALUES (NULL,26,'Coffee',10);
INSERT INTO OrderDetail VALUES (NULL,27,'Coffee',60);
INSERT INTO OrderDetail VALUES (NULL,27,'Cookie',28);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes','-1 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes','-1 days'),1);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime','-1 days'),1);

INSERT INTO OrderDetail VALUES (NULL,28,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,28,'Latte',30);
INSERT INTO OrderDetail VALUES (NULL,29,'Coffee',20);
INSERT INTO OrderDetail VALUES (NULL,30,'Coffee',60);
INSERT INTO OrderDetail VALUES (NULL,30,'Cookie',30);

INSERT INTO OrderMaster VALUES (NULL,'Bob',datetime('now','localtime','-3 minutes'),0);
INSERT INTO OrderMaster VALUES (NULL,'Alice',datetime('now','localtime','-1 minutes'),0);
INSERT INTO OrderMaster VALUES (NULL,'Bill',datetime('now','localtime'),0);

INSERT INTO OrderDetail VALUES (NULL,31,'Coffee',2);
INSERT INTO OrderDetail VALUES (NULL,31,'Latte',1);
INSERT INTO OrderDetail VALUES (NULL,32,'Coffee',1);
INSERT INTO OrderDetail VALUES (NULL,33,'Coffee',3);
INSERT INTO OrderDetail VALUES (NULL,33,'Cookie',3);
