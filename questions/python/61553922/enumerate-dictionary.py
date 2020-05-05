def show_menu(routers):
    router_list = []
    i = 0
    for router in routers:
        router_list.append("%s. %s " % ((i+2), router['name'],))
        i = i + 1

    menu_text = '\n'.join(router_list)

    print(("""
---------------------------------------------------------
0.EXIT
1.CONFIG ALL
"""+ menu_text +"""
---------------------------------------------------------
          """))

if __name__ == '__main__':
    show_menu([{
        'name': 'cisco_ios',
        'ip': '192.168.122.217',
        'username': 'admin',
        'password': '2020'
     },
     {
        'name': 'cisco_ios_123',
        'ip': '192.168.xxx.xxx',
        'username': 'admin',
        'password': '2021'
     }
     ])
