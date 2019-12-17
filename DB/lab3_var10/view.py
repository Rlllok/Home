import os

def print_table(table, table_name="table_name"):
    if table == None:
        return None
    print('-' * 80)
    print(table_name + ':')
    for row in table:
        print(row)
    print('-' * 80)

def clear():
    os.system('cls' if os.name == 'nt' else 'clear')

def print_select_table(database):
    clear()
    print_table_names(database)

def print_table_names(database):
    print('Available tables: ', end='')
    for table_name in database.table_names:
        print(table_name, end='  ')
    print()

def print_column_names(database, table_name):
    print('Column\'s names:')
    for column_name in database.get_column_names(table_name):
        if column_name != 'id':
            print(column_name, end='  ')
    print()

def print_main_menu():
    print('1. PRINT TABLE')
    print('2. UPDATE TABLE')
    print('3. INSERT TO TABLE')
    print('4. DELETE FROM TABLE')
    print('5. GENERATE RANDOM CUSTOMERS')
    print('6. GET VIDEO CARD BY ...')
    print('7 TEXT SEARCH')
    print('\n0. EXIT')

def print_get_by_menu():
    print('1. BY CORE')
    print('1. BY VENDOR')