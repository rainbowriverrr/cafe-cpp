CREATE TABLE IF NOT EXISTS OrderMaster (
    orderNumber INTEGER NOT NULL PRIMARY KEY,
    orderedBy TEXT NOT NULL,
    orderDate TEXT NOT NULL,
    isComplete INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS OrderDetail (
    orderDetailID INTEGER NOT NULL PRIMARY KEY,
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

CREATE TABLE InventoryItem (
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
