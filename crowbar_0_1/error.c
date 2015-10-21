void
crb_runtime_error(int line_number, RuntimeError id, ...)
{
	va_list		ap;
	VString		message;
	
	self_check();
	va_start(ap, id);
	clear_v_string(&message);
	format_message(&crb_runtime_error_message_format[id],
				   &message, ap);
	fprintf(stderr, "%3d:%s\n", line_number, message.string);
	va_end(ap);
	
	exit(1);
}