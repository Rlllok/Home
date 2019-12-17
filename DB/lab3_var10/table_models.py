import sqlalchemy as sqla
from sqlalchemy.ext.declarative import declarative_base


Base = declarative_base()


class Customers(Base):
    __tablename__ = 'customers'
    id = sqla.Column(sqla.Integer,
                     sqla.Sequence('cusromers_id_seq'),
                     primary_key=True)
    name = sqla.Column(sqla.String)
    account_balance= sqla.Column(sqla.Numeric)

    video_cards = sqla.orm.relationship("VideoCards", secondary="customers_videocards")
    
    def __init__(self, id, name, balance):
        self.id = id
        self.name = name
        self.account_balance = balance
    
    def __repr__(self):
        return ("<Customer(id='%i',name='%s', balance='%i')>" 
                % (self.id, self.name, self.account_balance))


class Manufacturers(Base):
    __tablename__ = 'manufacturers'
    id = sqla.Column(sqla.Integer,
                     sqla.Sequence('manufacturers_id_seq'),
                     primary_key=True)
    name = sqla.Column(sqla.String)
    video_card = sqla.orm.relationship('VideoCards', backref='manufacturers', lazy=True)

    def __repr__(self):
        return ("<Manufacturers(name='%s')>" 
                % (self.name))


class Vendors(Base):
    __tablename__ = 'vendors'
    id = sqla.Column(sqla.Integer,
                     sqla.Sequence('vendors_id_seq'),
                     primary_key=True)
    name = sqla.Column(sqla.String)

    video_cards = sqla.orm.relationship("VideoCards", secondary="vendors_videocards")

    def __repr__(self):
        return (f"<Vendor(id={self.id}, name='{self.name}')>")


class VideoCards(Base):
    __tablename__ = 'video_cards'
    id = sqla.Column(sqla.Integer,
                     sqla.Sequence('video_cards_id_seq'),
                     primary_key=True)
    name = sqla.Column(sqla.String)
    manufacturer_id = sqla.Column(sqla.Integer, sqla.ForeignKey('manufacturers.id'))
    ram = sqla.Column(sqla.Integer)
    core_clock = sqla.Column(sqla.Integer)
    memory_bus_width = sqla.Column(sqla.Integer)
    price = sqla.Column(sqla.Numeric)
    in_stock = sqla.Column(sqla.Integer)

    vendors = sqla.orm.relationship("Vendors", secondary="vendors_videocards")
    customers = sqla.orm.relationship("Customers", secondary="customers_videocards")

    def __repr__(self):
        return (f"<VideoCards(id='{self.id}', name='{self.name}', manufacturer_id='{self.manufacturer_id}', "
                f"ram='{self.ram}', core_clock='{self.core_clock}', memory_bus_width='{self.memory_bus_width}', "
                f"price='{self.price}', in_stock='{self.in_stock}')>")


class VendorsVideocards(Base):
    __tablename__ = 'vendors_videocards'
    vendor_id = sqla.Column(sqla.Integer, sqla.ForeignKey('vendors.id'), primary_key=True)
    video_card_id = sqla.Column(sqla.Integer, sqla.ForeignKey('video_cards.id'), primary_key=True)

    video_cards = sqla.orm.relationship(VideoCards, backref=sqla.orm.backref("vendors_videocards", cascade="all, delete-orphan"))
    vendors = sqla.orm.relationship(Vendors, backref=sqla.orm.backref("vendors_videocards", cascade="all, delete-orphan"))
    
    __table_args__ = (sqla.UniqueConstraint('vendor_id', 'video_card_id', name='vendors_videocards_vendor_id_video_card_id_key'),)

    def __repr__(self):
        return (f'<VendVideo(vendor_id={self.vendor_id}, '
                f'video_card_id={self.video_card_id})>')

class CustomersVideocards(Base):
    __tablename__ = 'customers_videocards'
    customer_id = sqla.Column(sqla.Integer, sqla.ForeignKey('customers.id'),
            primary_key=True)
    video_card_id = sqla.Column(sqla.Integer, 
            sqla.ForeignKey('video_cards.id'),
            primary_key=True)
    buy_data = sqla.Column(sqla.DateTime)
    amount = sqla.Column(sqla.Integer)

    video_cards = sqla.orm.relationship(VideoCards,
            backref=sqla.orm.backref("customers_videocards", 
                    cascade="all, delete-orphan"))
    customers = sqla.orm.relationship(Customers,
            backref=sqla.orm.backref("customers_videocards", 
                    cascade="all, delete-orphan"))

    def __repr__(self):
        return (f'<CusVid(cus_id={self.customer_id}, '
                f'video_id={self.video_card_id}, '
                f'date={self.buy_data}, '
                f'amount={self.amount})>')