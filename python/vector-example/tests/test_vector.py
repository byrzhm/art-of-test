import unittest
from vector import Vector

class TestVector(unittest.TestCase):
    def test_init(self):
        v = Vector(1, 2)
        self.assertEqual(v.x, 1)
        self.assertEqual(v.y, 2)

    def test_add(self):
        v1 = Vector(1, 2)
        v2 = Vector(3, 4)
        v3 = v1 + v2
        self.assertEqual(v3.x, 4)
        self.assertEqual(v3.y, 6)