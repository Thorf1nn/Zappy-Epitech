import unittest
from unittest.mock import MagicMock

from parsing import Parsing

class Test(unittest.TestCase):
    def test_parse_arguments(self):
        p = Parsing()
        p.set_things(1234, "team", "localhost")
        self.assertEqual(p.get_port(), 1234)
        self.assertEqual(p.get_name(), 'team')
        self.assertEqual(p.get_machine(), 'localhost')

    def test_error_handling(self):
        p = Parsing()
        p.parser.parse_args(['-p', '1234'])

        with self.assertRaises(SystemExit) as cm:
            p.error_handing()
        self.assertEqual(cm.exception.code, 84)

if __name__ == '__main__':
    unittest.main()

