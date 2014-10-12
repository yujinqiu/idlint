idlint
======

身份证校验小工具

## 编译

    sh build.sh

## 输入
身份证号码
## 输出
$success $gender
$success = 0  表示是符合规范的身份证
$gender  {0:女 1:男}

## 例子

    ./idlint <身份证号>
    