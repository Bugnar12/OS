for(i = 0 ; i < 4 ; i++)
{
	if(fork() && i % 2 == 1)
	{
		break;
	}
}
