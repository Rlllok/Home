import psycopg2
from config import config


class Database():
    conn = None
    params = config()
    table_names = []

    def __init__(self):
        try:
            self.conn = psycopg2.connect(**self.params)
            self.get_table_names()
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)

    def get_table_names(self):
        try:
            cur = self.conn.cursor()
            cur.execute('SELECT table_name FROM information_schema.tables'
                        ' WHERE table_schema = \'public\'')

            self.table_names = []

            for table_name in cur.fetchall():
                self.table_names.append(table_name[0])
            
            return self.table_names
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return None
        
    def get_from_table(self, table_name):
        result = []
        
        try:
            cur = self.conn.cursor()
            cur.execute(f'SELECT * FROM {table_name}')
            row = cur.fetchone()

            while row is not None:
                result.append(row)
                row = cur.fetchone()

            cur.close()

            return result
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return None

    def get_column_name_of_table(self, table_name):
        column_names = []

        try:
            cur = self.conn.cursor()
            cur.execute('SELECT column_name FROM information_schema.columns'
                        f' WHERE table_name = \'{table_name}\'')

            for column_name in cur.fetchall():
                column_names.append(column_name[0])
            
            cur.close()

            return tuple(column_names)
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return None

    def update_table(self, table_name, column_name, value, id):
        if table_name not in self.table_names:
            print('Wrong table name!')
            return False
        
        if column_name not in self.get_column_name_of_table(table_name):
            print('Wrong column name!')
            return False

        try:
            cur = self.conn.cursor()

            cur.execute(f'UPDATE {table_name} '
                        f'SET {column_name} = \'{value}\' '
                        f'WHERE {table_name}.id = {id};')
    

            self.conn.commit()
            cur.close()
            return True
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return False

    def insert_to_table(self, table_name, *values):
        if table_name not in self.table_names:
            print('Wrong table name!')
            return False

        try:
            cur = self.conn.cursor()
            #column's names without 'id'
            column_names = ', '.join(self.get_column_name_of_table(table_name)[1:])

            if len(values) == 1:
                cur.execute(f'INSERT INTO {table_name} ({column_names}) '
                            f'VALUES (\'{values[0]}\')')
            else:
                cur.execute(f'INSERT INTO {table_name} ({column_names}) '
                            f'VALUES {values}')
            
            self.conn.commit()
            cur.close()
            return True
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return False

    def delete_from_table(self, table_name, id):
        if table_name not in self.table_names:
            print('Wrong table name!')
            return False

        try:
            cur = self.conn.cursor()
            cur.execute(f'DELETE FROM {table_name} WHERE {table_name}.id = {id}')
            self.conn.commit()
            cur.close()
            return True
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return False

    def generate_random_customers(self, n):
        try:
            cur = self.conn.cursor()
            cur.execute(f'INSERT INTO customers (name, account_balance) '
                        f'SELECT * FROM generate_customers({n})')
            self.conn.commit()
            cur.close()
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)

    def get_manufacturers_videocards(self):
        try:
            cur = self.conn.cursor()
            cur.execute('SELECT manufacturers.name, video_cards.name '
                        'FROM manufacturers, video_cards '
                        'WHERE video_cards.manufacturer_id = manufacturers.id;')
        
            result = []
            row = cur.fetchone()
            while row is not None:
                result.append(row)
                row = cur.fetchone()
            return result
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return None

    def get_vendors_videocards(self):
        try:
            cur = self.conn.cursor()
            cur.execute('SELECT vendors.name, video_cards.name '
                        'FROM vendors, video_cards, vendors_videocards '
                        'WHERE vendors.id = vendors_videocards.vendor_id '
                        'AND video_cards.id = vendors_videocards.video_card_id;')
        
            result = []
            row = cur.fetchone()
            while row is not None:
                result.append(row)
                row = cur.fetchone()
            
            return result
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return None

    def get_videocards_by_core(self, min, max):
        try:
            cur = self.conn.cursor()
            cur.execute(f'SELECT * FROM video_cards '
                        f'WHERE video_cards.core_clock >= {min} '
                        f'AND video_cards.core_clock <= {max};')
        
            result = []
            row = cur.fetchone()
            while row is not None:
                result.append(row)
                row = cur.fetchone()
            
            return result
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return None
    
    def get_videocards_by_vendors(self, vendor_names):
        try:
            cur = self.conn.cursor()
            if len(vendor_names) == 1:
                cur.execute(f'SELECT vc.id, vc.name, vc.ram, vc.core_clock, '
                            f'vc.memory_bus_width, vc.in_stock, vendors.name '
                            f'FROM video_cards vc '
                            f'JOIN vendors_videocards '
                            f'ON vc.id = vendors_videocards.video_card_id ' 
                            f'JOIN vendors ON vendors.id = vendors_videocards.vendor_id '
                            f'WHERE vendors.name in (\'{vendor_names[0]}\');')
            else:
                cur.execute(f'SELECT vc.id, vc.name, vc.ram, vc.core_clock, '
                            f'vc.memory_bus_width, vc.in_stock, vendors.name '
                            f'FROM video_cards vc '
                            f'JOIN vendors_videocards '
                            f'ON vc.id = vendors_videocards.video_card_id ' 
                            f'JOIN vendors ON vendors.id = vendors_videocards.vendor_id '
                            f'WHERE vendors.name in {vendor_names};')
        
            result = []
            row = cur.fetchone()
            while row is not None:
                result.append(row)
                row = cur.fetchone()
        
            return result
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return False
    
    def full_text_search(self, search_str):
        try:
            cur = self.conn.cursor()
            search_list = search_str.split(' ')
            if len(search_list) == 1:
                cur.execute(f'SELECT vc_id, vc_name, manuf_name, ven_name '
                            f'FROM search_index '
                            f'WHERE document @@ to_tsquery(\'{search_list[0]}\');')
            else:
                search_argument = ' & '.join(search_list)
                cur.execute(f'SELECT vc_id, vc_name, manuf_name, ven_name '
                            f'FROM search_index '
                            f'WHERE document @@ to_tsquery(\'{search_argument}\');')
        
            result = []
            row = cur.fetchone()
            while row is not None:
                result.append(row)
                row = cur.fetchone()
            
            return result
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
            return False

    def disconnect(self):
        try:
            self.conn.close()
            name = self.params.get('database')
            print(f'Disconnected from database {name}')
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)