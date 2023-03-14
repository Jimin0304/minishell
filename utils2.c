//실제로 입력받은 문자열에서 리다이렉션 기호가 있으면 사용할 문자열의 앞뒤로 공백을 의미하는 -1을 넣고 리다이렉션 기호를 삽입
void	do_change_redir(char *str, char *s, t_index *idx, char op)
{
	if (s[idx->i] == op && s[idx->i + 1] == op)//리다이렉션 기호(>>)면 앞뒤로 -1 삽입
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else if (s[idx->i] == op)//(>)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else
		str[idx->j++] = s[idx->i++];
}

void	do_change_each_oper(char *str, char *s, t_index *idx, char op)
{
	if (s[idx->i] == op)//파이프 기호면 앞 뒤로 -1삽입
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else
		str[idx->j++] = s[idx->i++];
}
