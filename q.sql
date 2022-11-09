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
    price REAL NOT NULL
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

INSERT INTO MenuItem VALUES ("Coffee",2.29);
INSERT INTO MenuItem VALUES ("Latte",3.00);
INSERT INTO MenuItem VALUES ("Cappuccino",3.00);
INSERT INTO MenuItem VALUES ("Cookie",1.49);

INSERT INTO OrderMaster VALUES (NULL,"Bob","2022-11-08 10:22:00",0);
INSERT INTO OrderMaster VALUES (NULL,"Alice","2022-11-08 10:23:10",0);
INSERT INTO OrderMaster VALUES (NULL,"Bill","2022-11-08 10:23:45",0);

INSERT INTO OrderDetail VALUES (NULL,1,"Coffee",2);
INSERT INTO OrderDetail VALUES (NULL,1,"Latte",1);
INSERT INTO OrderDetail VALUES (NULL,2,"Coffee",1);
INSERT INTO OrderDetail VALUES (NULL,3,"Coffee",3);
INSERT INTO OrderDetail VALUES (NULL,3,"Cookie",3);
