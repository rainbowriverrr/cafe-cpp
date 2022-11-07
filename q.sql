CREATE TABLE OrderMaster (
    orderNumber INTEGER PRIMARY KEY,
    orderedBy TEXT NOT NULL,
    orderDate TEXT NOT NULL,
    isComplete INTEGER NOT NULL
);
