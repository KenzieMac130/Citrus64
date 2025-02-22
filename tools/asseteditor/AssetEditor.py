# By Kenzie Wright - SPDX-License-Identifier: Apache-2.0

import dearpygui.dearpygui as dpg
from pathlib import Path

def cb(sender, app_data):
    print(f"Main File is: {dpg.get_item_label(app_data)}")

def main():
    dpg.create_context()
    dpg.create_viewport(title="Citrus 64 Asset Editor")

    with dpg.window(tag="MAIN"):
        with dpg.menu_bar():
            with dpg.menu(label="File"):
                dpg.add_menu_item(label="New", shortcut="(Ctrl+N)")
                dpg.add_separator()
                dpg.add_menu_item(label="Open", shortcut="(Ctrl+O)")
                dpg.add_separator()
                dpg.add_menu_item(label="Save", shortcut="(Ctrl+S)")
                dpg.add_menu_item(label="Save All", shortcut="(Ctrl+Shift+S)")
                dpg.add_menu_item(label="Save As", shortcut="(Ctrl+Alt+S)")
                dpg.add_separator()
                dpg.add_menu_item(label="Exit")
            with dpg.menu(label="Edit"):
                dpg.add_menu_item(label="Undo", shortcut="(Ctrl+Z)")
                dpg.add_menu_item(label="Redo", shortcut="(Ctrl+Y)")
            with dpg.menu(label="Compile"):
                dpg.add_menu_item(label="Build and Test", shortcut="(F5)")

        with dpg.tab_bar(reorderable=True, callback=cb):
            with dpg.tab(label="My Main File"):
                dpg.add_text("Hii")
            with dpg.tab(label="My Main File 2"):
                dpg.add_text("Hii")
            for i in range(32):
                with dpg.tab(label=f"Aux {i}"):
                    pass

    dpg.setup_dearpygui()
    dpg.show_viewport()
    dpg.set_primary_window("MAIN", True)
    dpg.start_dearpygui()
    dpg.destroy_context()