CREATE TABLE IF NOT EXISTS OrderMaster (
    orderNumber INTEGER NOT NULL PRIMARY KEY,
    orderedBy TEXT NOT NULL,
    orderDate TEXT NOT NULL,
    status TEXT NOT NULL,
    sessionID TEXT NOT NULL
);

CREATE INDEX IF NOT EXISTS OrderDate ON OrderMaster(orderDate);

CREATE TABLE IF NOT EXISTS OrderDetail (
    orderDetailID INTEGER NOT NULL PRIMARY KEY,
    orderNumber INTEGER NOT NULL,
    menuItemName TEXT NOT NULL,
    quantity INTEGER NOT NULL
);

CREATE INDEX IF NOT EXISTS OrderDetailOrderNumber
    ON OrderDetail(orderNumber);

CREATE TABLE IF NOT EXISTS MenuItem (
    name TEXT NOT NULL PRIMARY KEY,
    price REAL NOT NULL,
    description TEXT NOT NULL
);

CREATE UNIQUE INDEX IF NOT EXISTS MenuItemName ON MenuItem(name);

CREATE VIEW IF NOT EXISTS vOrderDetail AS
    SELECT od.orderDetailID,
        od.orderNumber,
        od.menuItemName,
        od.quantity,
        m.price,
        (od.quantity * m.price) AS total
    FROM OrderDetail AS od
    LEFT OUTER JOIN MenuItem AS m ON m.name=od.menuItemName;

CREATE VIEW IF NOT EXISTS vOrderSales AS
    SELECT DATETIME(DATE(om.orderDate)) AS salesDate,
        od.menuItemName,
        SUM(od.quantity) AS totalQuantity,
        SUM(od.quantity * m.price) AS totalRevenue,
        0 AS isAllMenuItems
    FROM OrderDetail AS od
    INNER JOIN MenuItem AS m ON m.name=od.menuItemName
    INNER JOIN OrderMaster AS om ON om.orderNumber=od.orderNumber
    GROUP BY salesDate,menuItemName
    UNION
        SELECT DATETIME(DATE(om2.orderDate)) AS salesDate,
            'All menu items' AS menuItemName,
            SUM(od2.quantity) AS totalQuantity,
            SUM(od2.quantity * m2.price) AS totalRevenue,
            1 AS isAllMenuItems
        FROM OrderDetail AS od2
        INNER JOIN MenuItem AS m2 ON m2.name=od2.menuItemName
        INNER JOIN OrderMaster AS om2
            ON om2.orderNumber=od2.orderNumber
        GROUP BY salesDate;

CREATE TABLE IF NOT EXISTS InventoryItem (
    itemID INTEGER NOT NULL PRIMARY KEY,
    itemName TEXT NOT NULL,
    quantity INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS MenuItemIngredient (
    menuItemName TEXT NOT NULL,
    inventoryItemID TEXT NOT NULL,
    quantity INTEGER NOT NULL,
    PRIMARY KEY (menuItemName,inventoryItemID)
);

CREATE TABLE IF NOT EXISTS Admin (
    userName TEXT NOT NULL PRIMARY KEY,
    password TEXT NOT NULL
);
