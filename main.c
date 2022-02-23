int main()
{
	int i = 0;
	char	*test;

	test = (const char *)strdup("testiwehjklrwhkkdrh;dfgkhjfgklhjd;lfjhfgkhljfdlkjdkl");
	free(test);
	test = 0;
	while (test && test[1000])
		printf("-%d\n", i++);
	write(1, "lol\n", 4);
}
