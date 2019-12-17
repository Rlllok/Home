import sqlalchemy as sqla
from sqlalchemy.ext.declarative import declarative_base

from config import config
import table_models


class Database():
    engine = None
    Base = table_models.Base
    params = config()
    table_names = []

    def __init__(self):
            user = self.params.get('user')
            password = self.params.get('password')
            host = self.params.get('host')
            database = self.params.get('database')

            url = f'postgresql://{user}:{password}@{host}/{database}'
            self.engine = sqla.create_engine(url)
            self.connection = self.engine.connect()
            self.table_names = self.Base.metadata.tables.keys()

    def get_from_table(self, model):
        self.session = sqla.orm.Session(bind=self.connection)
        result = self.session.query(model).all()
        return result

    def get_column_names(self, model):
        return model.__table__.columns.keys()

    def update_table(self, model, column_name, value, id):
        self.session = sqla.orm.Session(bind=self.connection)
        self.session.query(model).filter(model.id == id).\
            update({column_name: value})
        self.session.commit()

    def insert_to_table(self, table_name, *values):
        id = self.connection.execute(
                sqla.Sequence(f'{table_name.__table__}_id_seq'))
        row = table_name(id, *values)
        self.session = sqla.orm.Session(bind=self.connection)
        self.session.add(row)
        self.session.commit()