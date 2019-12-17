DROP TABLE video_cards;
DROP TABLE customers;
DROP TABLE customers_videocards;
DROP TABLE manufacturers;
DROP TABLE vendors;
DROP TABLE vendors_videocards;

CREATE TABLE IF NOT EXISTS manufacturers (
    id SERIAL NOT NULL PRIMARY KEY,
    name VARCHAR UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS video_cards (
    id SERIAL NOT NULL PRIMARY KEY,
    name VARCHAR NOT NULL,
    manufacturer_id INT NOT NULL,
    ram INT NOT NULL,
    core_clock INT NOT NULL,
    memory_bus_width INT NOT NULL,
    price NUMERIC NOT NULL,
    in_stock INT NOT NULL,
    FOREIGN KEY (manufacturer_id) REFERENCES manufacturers(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS customers (
    id SERIAL NOT NULL PRIMARY KEY,
    name VARCHAR NOT NULL,
    account_balance NUMERIC NOT NULL DEFAULT 0
);

CREATE TABLE IF NOT EXISTS customers_videocards (
    customer_id INT NOT NULL,
    video_card_id INT NOT NULL,
    buy_data timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
    amount INT NOT NULL,
    FOREIGN KEY (customer_id) REFERENCES customers(id) ON DELETE CASCADE,
    FOREIGN KEY (video_card_id) REFERENCES video_cards(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS vendors (
    id SERIAL NOT NULL PRIMARY KEY,
    name VARCHAR UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS vendors_videocards (
    vendor_id INT NOT NULL,
    video_card_id INT NOT NULL,
    UNIQUE (vendor_id, video_card_id),
    FOREIGN KEY (vendor_id) REFERENCES vendors(id) ON DELETE CASCADE,
    FOREIGN KEY (video_card_id) REFERENCES video_cards(id) ON DELETE CASCADE
);


INSERT INTO manufacturers (name) VALUES ('AMD');
INSERT INTO manufacturers (name) VALUES ('NVIDIA');

INSERT INTO vendors (name) VALUES ('ASUS');
INSERT INTO vendors (name) VALUES ('Sapphire');
INSERT INTO vendors (name) VALUES ('MSI');
INSERT INTO vendors (name) VALUES ('Gigabyte');

INSERT INTO video_cards (name, manufacturer_id, ram, core_clock, memory_bus_width, price, in_stock)
VALUES ('PCI-Ex GeForce GTX 1660 Ti', 2, 6000, 1875, 192, 199.99, 200); -- MSI
INSERT INTO video_cards (name, manufacturer_id, ram, core_clock, memory_bus_width, price, in_stock)
VALUES ('PCI-Ex GeForce GTX 1660 Ti', 2, 6000, 1875, 192, 185.99, 110); --GIGABYTE
INSERT INTO video_cards (name, manufacturer_id, ram, core_clock, memory_bus_width, price, in_stock)
VALUES ('PCI-Ex GeForce RTX 2070 Super', 2, 8000, 1605, 256, 350, 80); --Asus
INSERT INTO video_cards (name, manufacturer_id, ram, core_clock, memory_bus_width, price, in_stock)
VALUES ('PCI-Ex Radeon RX 580', 1, 4000, 1366, 256, 160.99, 180); --Sapphire
INSERT INTO video_cards (name, manufacturer_id, ram, core_clock, memory_bus_width, price, in_stock)
VALUES ('PCI-Ex Radeon RX 5700 XT', 1, 8000, 1650, 256, 300, 125); --Gigabyte

INSERT INTO vendors_videocards (vendor_id, video_card_id) VALUES (3, 1);
INSERT INTO vendors_videocards (vendor_id, video_card_id) VALUES (4, 2);
INSERT INTO vendors_videocards (vendor_id, video_card_id) VALUES (1, 3);
INSERT INTO vendors_videocards (vendor_id, video_card_id) VALUES (3, 4);
INSERT INTO vendors_videocards (vendor_id, video_card_id) VALUES (4, 5);

INSERT INTO customers (name) VALUES ('Novikov');
INSERT INTO customers (name, account_balance) VALUES ('Tyrkin', 2500);

INSERT INTO customers_videocards (customer_id, video_card_id, buy_data, amount) VALUES (1, 3, '2019-06-21', 1);
INSERT INTO customers_videocards (customer_id, video_card_id, buy_data, amount) VALUES (2, 5, '2019-09-10', 2);