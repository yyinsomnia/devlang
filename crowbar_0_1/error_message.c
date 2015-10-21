MessageFormat crb_compile_error_message_format[] = {    
	{ "dummy"},    { "($(token) 附近有语法错误)"},
	{ " 错误的字符($(bad_char))"},
	{ " 函数名重复($(name))"},
	{ "dummy"},
};

MessageFormat crb_runtime_error_message_format[] = {
	{ "dummy"},
	{ " 找不到变量($(name))。"},
	{ " 找不到函数($(name))。"},
	{ " 传递的参数多于函数所要求的参数。"},
	{ " 传递的参数少于函数所要求的参数。"},
	{ " 条件语句类型必须为boolean 型"},
	…
	{ "dummy"},
};