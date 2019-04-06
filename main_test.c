int main(void)
{
	char *test;

	test = malloc(1);
	printf("ret : %d\n", free(test));
}
