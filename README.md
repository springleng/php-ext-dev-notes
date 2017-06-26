# php-ext-dev-notes

PHP extensions Development Notes, Based on php 7.1.x version.

Links:
[PHP扩展开发及内核应用] (http://www.cunmou.com/phpbook/index.md)
and
[PHP7内核剖析] (https://github.com/pangudashu/php7-internal)

## 1、使用 ext_skel 脚本创建扩展

```shell
cd php-7.1.x/ext
./ext_skel --extname=myfunctions --proto=myfunctions.def
```
