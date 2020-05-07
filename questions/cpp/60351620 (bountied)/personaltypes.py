from dumper import *

def qdump__TestClass(d, value):
    d.putValue("TestClass")
    d.putNumChild(2)
    if d.isExpanded():
        with Children(d):
            d.putSubItem("x", value["x"])
            d.putSubItem("y", value["y"])
