# php-ext-dev-notes

>PHP extensions Development Notes, Based on php 7.1.x version.

>Reference links:
[PHP7 Internal @laruence](https://github.com/laruence/php7-internal)
,
[PHP7内核剖析 @pangudashu](https://github.com/pangudashu/php7-internal)
,
[PHP扩展开发及内核应用 @walu](http://www.cunmou.com/phpbook/index.md)
and
[PHP扩展开发笔记 @Leon2012](https://github.com/Leon2012/php-ext)

##### 1、使用 ext_skel 脚本创建扩展

```shell
cd php-7.1.x/ext
./ext_skel --extname=myfunctions --proto=myfunctions.def
```
