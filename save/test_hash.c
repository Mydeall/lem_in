#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "includes/libft.h"
#define SIZE_HASH 9679
#define NB_OBJ 6500

typedef struct	s_room
{
	char 			*name;
	struct s_room	*next;
}				t_room;

int		hash_classic(char *name) {
	int accum;
	int len;

	len = strlen(name);
	accum = 0;
	while(len-- > 0) 
	{
		accum = accum << 1;
		accum += (unsigned)(*name++ & 0xFF);        
	}
	return (accum % SIZE_HASH);
}

int		hash_rodolphe(char *name) {
	int len;
	int	key;

	len = strlen(name);
	key = 1223;
	while(len-- > 0) 
		key = (key * 11) ^ (name[len] * 131);
	return (key % SIZE_HASH);
}

int		hash_fowler_noll(char *name)
{
	unsigned long int hash;
	const unsigned char* ptr;
	int len;
	int prime;

	len = strlen(name);
	prime = 16777619;
	hash = 2166136261;
	ptr = (const unsigned char*)name;
	while(len-- > 0) 
		hash = ((*ptr++) ^ hash) * prime;
	printf("hash : %lu\n", hash);
	return ((unsigned int)(hash % SIZE_HASH));
}

int		hash_jenkins(char *name)
{
	int	i;
	unsigned int hash;

	i = -1;
	hash = 0;
	ft_putendl(name);
	while (name[++i])
	{
		hash += name[i];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return (int)(hash % SIZE_HASH);
}

char	*gen_name(void)
{
	int		random;
	char	*name;
	int		i;

	name = (char*)malloc(5);
	name[4] = 0;
	i = -1;
	while (++i < 4)
		name[i] = rand() % (122-97) + 97;
//	printf("name : %s\n", name);
	return (name);
}

int		print_tab(t_room *(hash_tab[SIZE_HASH]))
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (++i < SIZE_HASH)
		if (hash_tab[i] != NULL)
		{
//			printf("%d : %s\n", i, hash_tab[i]);
			count++;
		}
	return (count);
}

int main()
{
	int		hash;
	char	*name;
	int		i;
	int		j;
	int		max;
	t_room	**hash_tab;
	t_room	*tmp;
	t_room	*new;
	int		nb_coli;
	int 	nb_cel;

	hash_tab = (t_room**)ft_memalloc(sizeof(t_room*) * SIZE_HASH);
	srand(time(NULL));
	i = -1;
	max = 0;
	nb_coli = 0;
	while (++i < NB_OBJ)
	{
		name = gen_name();
//		hash = hash_classic(name);
		hash = hash_rodolphe(name);
//		hash = hash_fowler_noll(name);
//		hash = hash_jenkins(name);
		new = (t_room*)malloc(sizeof(*new));
		new->next = NULL;
		new->name = name;
		j = 0;
		if (hash_tab[hash])
		{
			nb_coli++;
			tmp = hash_tab[hash];
			while (tmp->next)
			{
				tmp = tmp->next;
				j++;
			}
			if (j > max)
				max = j;		
			tmp->next = new; 
//			printf("collision --> %d : %s\n", hash, hash_tab[hash]);
		}
		else
			hash_tab[hash] = new;
	}
	nb_cel = print_tab(hash_tab);
	printf("\n-----------------------\n");
	printf("Nombre de salles : %d\nTaille tab hash : %d\n", NB_OBJ, SIZE_HASH);
	printf("Nombre de collisions : %d\nNombre de cases occupees : %d / %d\n", nb_coli, nb_cel, SIZE_HASH);
	printf("Facteur de compression : %.2f\n", (double)nb_cel / (double)SIZE_HASH);
	printf("Occupation maximale d'une case : %d\n", max);
	return (0);
}
