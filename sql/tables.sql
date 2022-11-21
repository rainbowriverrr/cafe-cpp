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

CREATE VIEW IF NOT EXISTS vOrderSales AS
    SELECT DATETIME(DATE(om.orderDate)) AS salesDate,
        vod.menuItemName,
        SUM(vod.quantity) AS totalQuantity,
        SUM(vod.total) AS totalRevenue,
        0 AS isAllMenuItems
    FROM vOrderDetail AS vod
    LEFT OUTER JOIN OrderMaster AS om ON om.orderNumber=vod.orderNumber
    WHERE om.isComplete = 1
    GROUP BY salesDate,menuItemName
    UNION
        SELECT DATETIME(DATE(om2.orderDate)) AS salesDate,
            'All menu items' AS menuItemName,
            SUM(vod2.quantity) AS totalQuantity,
            SUM(vod2.total) AS totalRevenue,
            1 AS isAllMenuItems
        FROM vOrderDetail AS vod2
        LEFT OUTER JOIN OrderMaster AS om2
            ON om2.orderNumber=vod2.orderNumber
        WHERE om2.isComplete = 1
        GROUP BY salesDate
    ORDER BY salesDate,isAllMenuItems DESC,menuItemName;

