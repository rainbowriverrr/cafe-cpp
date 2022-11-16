CREATE TABLE IF NOT EXISTS OrderMaster (
    orderNumber INTEGER PRIMARY KEY,
    orderedBy TEXT NOT NULL,
    orderDate TEXT NOT NULL,
    isComplete INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS OrderDetail (
    orderDetailID INTEGER PRIMARY KEY,
    orderNumber INTEGER NOT NULL,
    menuItemName TEXT NOT NULL,
    quantity INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS MenuItem (
    name TEXT NOT NULL PRIMARY KEY,
    price REAL NOT NULL,
    description TEXT NOT NULL
);
CREATE VIEW IF NOT EXISTS vOrderDetail AS
SELECT od.orderDetailID,
    od.orderNumber,
    od.menuItemName,
    od.quantity,
    m.price,
    (quantity * price) AS total
    FROM OrderDetail AS od
    LEFT OUTER JOIN MenuItem AS m ON m.name = od.menuItemName;

DELETE FROM MenuItem;
DELETE FROM OrderMaster;
DELETE FROM OrderDetail;

INSERT INTO MenuItem VALUES ("Undefined Symbol",2.29, "Blonde Roast");
INSERT INTO MenuItem VALUES ("Memory Leak",3.00, "Medium Roast");
INSERT INTO MenuItem VALUES ("Segmentation Fault",3.00, "Dark Roast");
INSERT INTO MenuItem VALUES ("GNUppaccino",3.49, "Cappuccino");
INSERT INTO MenuItem VALUES ("Stack Overflow",10.49, "Big Fat Hamburger");

INSERT INTO OrderMaster VALUES (NULL,"Bob","2022-11-08 10:22:00",0);
INSERT INTO OrderMaster VALUES (NULL,"Alice","2022-11-08 10:23:10",0);
INSERT INTO OrderMaster VALUES (NULL,"Bill","2022-11-08 10:23:45",0);

INSERT INTO OrderDetail VALUES (NULL,1,"Coffee",2);
INSERT INTO OrderDetail VALUES (NULL,1,"Latte",1);
INSERT INTO OrderDetail VALUES (NULL,2,"Coffee",1);
INSERT INTO OrderDetail VALUES (NULL,3,"Coffee",3);
INSERT INTO OrderDetail VALUES (NULL,3,"Cookie",3);
