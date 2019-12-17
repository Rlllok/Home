import model
import view

import time


def main():
    database = model.Database()

    main_menu(database)
    
    database.disconnect()


def main_menu(database):
    while True:
        view.print_main_menu()
        choice = input('Input your choice: ')

        while choice == '0':  
            return

        # PRINT
        while choice == '1':
            view.print_select_table(database)
            if select_menu(database) == True:
                break
            else:
                print('Wrong table name!')
                time.sleep(1)

        #UPDATE
        while choice == '2':
            if update_menu(database) == True:
                break
            else:
                print('Wrong table or column name!')
                time.sleep(1)

        #INSERT
        while choice == '3':
            if insert_menu(database) == True:
                break
            else:
                print('Wrong table name!')
                time.sleep(1)

        #DELETE
        while choice == '4':
            if delete_menu(database) == True:
                break
            else:
                print('Wrong table name!')
                time.sleep(1)

        #GENERATE
        while choice == '5':
            if generate_customers_menu(database) == True:
                break
            else:
                print('Wrong numbere!')
                time.sleep(1)

        #GET BY
        while choice == '6':
            if get_by_menu(database) == True:
                break

        #TEXT SEARCH
        while choice == '7':
            if text_search_menu(database) == True:
                break


def select_menu(database):
    table_name = input('Input table name: ')

    if table_name not in database.table_names:
        return False
    else:
        view.clear()
        view.print_table(database, 
                database.get_from_table(table_name), table_name)
        return True


def update_menu(database):
    view.print_table_names(database)
    table_name = input('Input table name: ')

    if table_name not in database.table_names:
        return False
    else:
        view.print_column_names(database, table_name)
        column_name = input('Input column name: ')
        
        if column_name not in database.get_column_name_of_table(table_name):
            return False
        else:
            value = input('Input value: ')
            update_id = input('Input id: ')
            database.update_table(table_name, column_name, value, update_id)
            return True


def insert_menu(database):
    view.clear()
    view.print_table_names(database)
    table_name = input('Input table name: ')

    if table_name not in database.table_names:
        return False
    else:
        view.print_column_names(database, table_name)
        values = input('Input values for columns separeted by space: ').split()
        database.insert_to_table(table_name, *values)
        return True


def delete_menu(database):
    view.clear()
    view.print_table_names(database)
    table_name = input('Input table name: ')

    if table_name not in database.table_names:
        return False
    else:
        delete_id = input('Input id to delete: ')
        database.delete_from_table(table_name, delete_id)
        return True
        

def generate_customers_menu(database):
    view.clear()
    num_to_generate = input('Input a number of customers to generate: ')

    if int(num_to_generate) <= 0:
        return False

    database.generate_random_customers(num_to_generate)
    return True


def get_by_menu(database):
    view.clear()
    view.print_get_by_menu()

    choice = input('Input your choice: ')

    while True:
        while choice == '1':
            view.clear()
            min_core = input('Input min core value: ')
            max_core = input('Input max core value: ')

            if (int(min_core)<0 
                    or int(max_core)<0 
                    or int(min_core)>int(max_core)):
                print('Wrong values!')
                time.sleep(1)
            else:
                view.print_table(database,
                    database.get_videocards_by_core(min_core, max_core)
                    )
                return True
        while choice == '2':
            view.clear()
            vendors = input('Input vendor separeted by space: ').split()
            print(vendors)
            
            view.print_table(database,
                    database.get_videocards_by_vendors(vendors)
                    )
            return True
            
        while choice == '3':
            return False


def text_search_menu(database):
    view.clear()
    search_str = input('Input word or phrase to search: ')
    
    if view.print_table(database,
            database.full_text_search(search_str)):
        return True
    else:
        print(f'Cannot find \'{search_str}\'')
        return True


def print_update(database):
    table_name = input('Input table name: ')
    table_name = table_name.lower()

    if table_name not in database.table_names:
        print('Wrong table name')
        return False
    else:
        pass


if __name__ == "__main__":
    main()

# SELECT manufacturers.name, video_cards.name FROM manufacturers, video_cards 
# WHERE video_cards.manufacturer_id = manufacturers.id;

# SELECT vendors.name, video_cards.name FROM vendors, video_cards, vendors_videocards
# WHERE vendors.id = vendors_videocards.vendor_id AND video_cards.id = vendors_videocards.video_card_id;

# -- SELECT * FROM video_cards WHERE video_cards.core_clock >= 1000 AND video_cards.core_clock <= 3000;

# -- SELECT video_cards.name FROM video_cards
# -- WHERE video_cards.id = (select video_card_id from vendors_videocards where vendors_videocards.vendor_id =  
# -- (select vendors.id from vendors where vendors.name = 'ASUS' or vendors.name = 'MSI'))

# SELECT vc.id, vc.name, vc.ram, vc.core_clock, vc.memory_bus_width, vc.in_stock, vendors.name 
# FROM video_cards vc
# JOIN vendors_videocards ON vc.id = vendors_videocards.video_card_id
# JOIN vendors ON vendors.id = vendors_videocards.vendor_id
# WHERE vendors.name in ('ASUS', 'MSI');

# SELECT vc_id, vc_name, manuf_name, ven_name
# FROM search_index
# WHERE document @@ to_tsquery('2070');
