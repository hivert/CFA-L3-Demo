# coding=utf-8

class EmptyListError(Exception):
    pass

NoneType = type(None)

class Cell(object):
    __slots__ = ("value", "next_cell")
    def __init__(self, val, lst):
        assert(isinstance(lst, (Cell, List, NoneType)))
        self.value = val
        if isinstance(lst, List):
            lst = lst.next_cell
        self.next_cell = lst


class List(Cell):
    """
    Liste chainée

    Les cellules sont numérotées à partir de 1, la cellule 0, n'est pas
    utilisée.

    sage: L = List()
    sage: L.is_empty()
    True
    sage: L.length()
    0
    sage: L.first_cell().value
    Traceback (most recent call last):
    ...
    EmptyListError
    sage: L = List(Cell(1, List()))
    sage: L.first_cell().value
    1
    sage: L.first_cell().next_cell == None
    True
    sage: L
    ->[1]->
    sage: L.insert(3); L
    ->[3]->[1]->
    sage: L.insert(2); L
    ->[2]->[3]->[1]->
    sage: L.insert(12, 1); L
    ->[2]->[12]->[3]->[1]->
    sage: L.ith_cell(2).value
    12
    sage: L.delete(2); L
    ->[2]->[12]->[1]->
    sage: L.length()
    3
    sage: L.insert(24, L.length()); L
    ->[2]->[12]->[1]->[24]->
    """
    def __init__(self, c = None):
        Cell.__init__(self, "Unused", c)

    def is_empty(self):
        return self.next_cell is None

    def first_cell(self):
        if self.next_cell:
            return self.next_cell
        else:
            raise EmptyListError

    def ith_cell(self, i):
        cur = self
        for _ in range(i):
            if cur.next_cell:
                cur = cur.next_cell
            else:
                raise EmptyListError
        return cur

    def insert(self, val, i=0):
        cur = self.ith_cell(i)
        cur.next_cell = Cell(val, cur.next_cell)

    def delete(self, i=0):
        cur = self.ith_cell(i)
        if cur.next_cell is None:
            raise EmptyListError
        cur.next_cell = cur.next_cell.next_cell

    def length(self):
        res = 0
        cur = self
        while cur.next_cell:
            cur = cur.next_cell
            res += 1
        return res

    def __repr__(self):
        res = "->"
        cur = self
        while cur.next_cell:
            cur = cur.next_cell
            res += "[%s]->"%(cur.value)
        return res
