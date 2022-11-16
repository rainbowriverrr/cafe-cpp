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

