INSERT INTO MenuItem VALUES ("Undefined Symbol",2.29, "Blonde Roast");
INSERT INTO MenuItem VALUES ("Memory Leak",3.00, "Medium Roast");
INSERT INTO MenuItem VALUES ("Segmentation Fault",3.00, "Dark Roast");
INSERT INTO MenuItem VALUES ("GNUppuccino",3.49, "Cappuccino");
INSERT INTO MenuItem VALUES ("Stack Overflow",10.49, "Big Fat Hamburger");

INSERT INTO OrderMaster VALUES (NULL,"Bob","2022-11-08 10:22:00",0,"sess-1");
INSERT INTO OrderMaster VALUES (NULL,"Alice","2022-11-08 10:23:10",0, "sess-2");
INSERT INTO OrderMaster VALUES (NULL,"Bill","2022-11-08 10:23:45",0, "sess-3");

INSERT INTO OrderDetail VALUES (NULL,1,"Coffee",2);
INSERT INTO OrderDetail VALUES (NULL,1,"Latte",1);
INSERT INTO OrderDetail VALUES (NULL,2,"Coffee",1);
INSERT INTO OrderDetail VALUES (NULL,3,"Coffee",3);
INSERT INTO OrderDetail VALUES (NULL,3,"Cookie",3);
