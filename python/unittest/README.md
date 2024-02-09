### tests 文件夹中的每个测试文件必须以 test_ 开头

如 `test_vector.py`

### test 文件内容

- 首先 `import unittest`, 我们的Test类必须继承`unittest.TestCase`
- Test类命名必须以`Test`为前缀或后缀
- 每个Test类中可以有若干Test方法, 所有的Test方法必须以`test_`为前缀

``` python
import unittest
from vector import Vector

class TestVector(unittest.TestCase):
    def test_init(self):
        v = Vector(1, 2)
        self.assertEqual(v.x, 1)
        self.assertEqual(v.y, 2)
```

#### self.assert...

- `assertTrue`
- `assertFalse`
- `assertEqual`
- ...

#### 测试程序是否能够正常抛出异常

```python
with self.assertRaises(ValueError):
    v = Vector("1", "2")
```

#### 在每个Test方法调用前后的回调函数

- `setUp` 在每个Test方法前调用
- `tearDown` 在每个Test方法后调用

``` python
class TestVector(unittest.TestCase):
    ...
    def setUp(self):
        print("start")
```

#### 在每个Test类创建前与销毁时的回调函数

- `setUpClass`
- `tearDownClass`

``` python
class TestVector(unittest.TestCase):
    ...
    @classmethod
    def setUpClass(self):
        print("start")
```

#### 条件测试

```python
# 平台
@unittest.skipIf(sys.platform == "win32", "Do not support Windows")
# python 版本
@unittest.skipIf(sys.version < (3, 7), "Only support 3.7+")
```

### 运行 unittest

#### 运行所有 unittest

```shell
# 在主目录下
python -m unittest
```

#### 运行指定的 unittest

```shell
# 在主目录下
# 运行指定module
python -m unittest tests.test_vector
# 运行指定class
python -m unittest tests.test_vector.TestVector
# 运行指定method
python -m unittest tests.test_vector.TestVector.test_init
```