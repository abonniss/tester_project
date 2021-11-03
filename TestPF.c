#include <stdio.h>
#include <stdbool.h>
#include "ft_printf.h"
#include <limits.h> 

size_t test_neg = 0;
size_t test_pos = 0;

bool memeq(void *ptr1, void *ptr2, size_t len_ptr1, size_t len_ptr2)
{
	if (((ptr1 == NULL || ptr2 == NULL) && (ptr1 != ptr2)) || len_ptr1 != len_ptr2)
		return (false);
	if (ptr1 == NULL && ptr2 == NULL)
		return (true);
	for (size_t i = 0; i < len_ptr1; ++i)
	{
		if (((char *)ptr1)[i] != ((char *)ptr2)[i])
			return (false);
	}
	return (true);
}

int tester(const char *name, const char *input, ...)
{
	va_list args_1;
	va_list args_2;
	int ret_1;
	int ret_2;
	char *output_1 = NULL;
	char *output_2 = NULL;
	bool ret_test;
	static int test_nb = 1;

	va_start(args_1, input);
	va_copy(args_2, args_1);
	ret_1 = vasprintf(&output_1, input, args_1); 
	ret_2 = ft_vasprintf(&output_2, input, args_2); 
	va_end(args_1);
	va_end(args_2);
	ret_test = memeq(output_1, output_2, ret_1, ret_2);
	printf("TEST %-3d | \"%s\" -------> %s\033[0m\n", test_nb, name, ret_test ? "\033[32mOK" : "\033[31mKO");
	if (ret_test == false)
	{
	 	printf("output_as -> [%s]  (%d)\noutput_ft -> [%s]  (%d)\n\n", output_1, ret_1, output_2, ret_2);
		test_neg++;
	}
	else {
		test_pos++;
	}
	free(output_1);
	free(output_2);
	test_nb++;
	return (ret_test);
}

// Rajout des tests mulitple - Ratio de tests fonctionnel - 

int main()
{
	tester("%di - Chiffre 0", "%d", 0);
	tester("%di - Chiffres entier positif", "%d", 1);
	tester("%di - Chiffres entier negatif", "%d", -1);
	tester("%di - Int Max", "%d", INT_MAX);
	tester("%di - Int Max Depasse", "%d", INT_MAX + 1);
	tester("%di - Int Min", "%d", INT_MIN);
	tester("%di - Int Min Depasse", "%d", INT_MIN - 1);
	tester("%di - Passage Frmt decimal - N", "%d", 2.1);
	
	tester("%xx - Chiffre 0", "%x", 0);
	tester("%xx - Chiffres entier positif", "%x", 1);
	tester("%xx - Chiffres entier negatif", "%x", -1);
	tester("%xx - Chiffres entier negatif 2", "%x", -42);
	tester("%xx - Int Max", "%x", INT_MAX);
	tester("%xx - Int Max Depasse", "%x", INT_MAX + 1);
	tester("%xx - Int Min", "%x", INT_MIN);
	tester("%xx - Int Min Depasse", "%x", INT_MIN - 1);
	tester("%xx - Passage Frmt decimal - NC", "%x", 2.1);
	
	tester("%xX - Chiffre 0", "%X", 0);
	tester("%xX - Chiffres entier positif", "%X", 1);
	tester("%xX - Chiffres entier negatif", "%X", -1);
	tester("%xX - Chiffres entier negatif 2", "%X", -42);
	tester("%xX - Int Max", "%X", INT_MAX);
	tester("%xX - Int Max Depasse", "%X", INT_MAX + 1);
	tester("%xX - Int Min", "%X", INT_MIN);
	tester("%xX - Int Min Depasse", "%X", INT_MIN - 1);
	tester("%xX - Passage Frmt decimal - NC", "%X", 2.1);

	tester("%u - Chiffre 0", "%u", 0);
	tester("%u - Chiffres entier positif", "%u", 1);
	tester("%u - Chiffres entier negatif - NC", "%u", -1);
	tester("%u - Unsigned Int Max", "%u", UINT_MAX);
	tester("%u - Unisgned Int Max Depasse - NC", "%u", UINT_MAX + 1);
	tester("%u - Passage Frmt decimal", "%u", 2.1);

	tester("Texte sans format", "Une phrase");
	tester("Texte long sans format", "C’est une informaticienne chevronnée de 35 ans. Une surdouée qui s’est découvert une passion pour l’informatique à l’âge de treize ans lorsqu’elle a vu une publicité pour cet ordinateur familial dont on ventait les mérites à l’aide d’une petite marionnette virtuelle. Elle voulait un ami, elle a eu une marionnette virtuelle. Depuis, la marionnette a laissé place à des projets plus sérieux, plus lucratifs surtout. Mais Sophie, c’est comme ça qu’elle nommait sa marionnette, est toujours là, dans un petit coin de son ordinateur et c’est à Sophie qu’elle s’adresse quand le moral est au plus bas. Mais aujourd’hui, c’est Sophie qui s’adresse à Florence.");
	tester("Texte vide[]", "");

	tester("%s - String", "%s", "Une phrase");
	tester("%s - String vide ou [\\0]", "%s", "");
	tester("%s - String a l'interieur", "Inception (%s)", "avec une phrase");
	tester("%s - String passage pointeur NULL", "%s", NULL);
	tester("%s - String multiple", "(%s)-->(%s)-->(%s)-->(%s)-->(%s)", "Une", "Phrase", "Qui", "Se", "Decoupe");


	tester("%c - Char", "%c", 'C');
	tester("%c - Char \\0", "%c",'\0');
	tester("%c - Char passage d'un chiffre 97 = a", "%c", 97);
	tester("%c - Char passage d'un caractère non affichablee 6 = ack", "%c", 6);
	tester("%c - Char passage d'un chiffre hors ASCII 1254 - NC", "%c", 1254);
	tester("%c - Char passage d'un chiffre hors ASCII 160 - NC", "%c", 160);
	tester("%c - Char passage d'un chiffre hors ASCII Negatif -60 - NC", "%c", -60);
	tester("%c - Phrase avec (c) =[\\0] au milieu", "Une phrase avec %c au milieu de la phrase%", '\0');

	tester("%% - Double Pourcentage", "(%%)");
	tester("%% - Triple Pourcentage", "%%%");
	tester("%% - Quadruple Pourcentage", "(%%%%)");
	tester("%% - Simple Pourcentage", "%");

	tester("%p - Impression d'un pointeur - Nbr", "(%p)", 120);
	tester("%p - Impression d'un pointeur - Nbr neg", "(%p)", -120);
	tester("%p - Impression d'un pointeur - Ulongmax", "(%p)", ULONG_MAX);
	tester("%p - Impression d'un pointeur - Longmin", "(%p)", LONG_MIN);
	tester("%p - Impression d'un pointeur - IntMin", "(%p)", INT_MIN);
	tester("%p - Impression d'un pointeur - Str - on envoie direct l'adresse - guillemet = adresse", "(%p)", "Ceci est une phrase");
	tester("%p - Impression d'un pointeur - NULL", "(%p)", NULL);
	tester("%p - Impression d'un pointeur - Str vide = test identique qu'une str\"\"  ", "");


	tester("% - Modifier inconnu (r)", "%r");
	tester("% - Modifier inconnu (r) et passage de 100", "%r", 100);
	tester("% - Modifier inconnu (r)", "%r test d'une phrase");


	tester("%Multi", "Une s suivi d'un d suivi d'un x avec c colle %s%d%x%c", "Salut", 87, 1545,'c');
	tester("% - Modifier inconnu (r)", "%r test d'une phrase");
	tester("% - Modifier inconnu (r)", "%r test d'une phrase");
	tester("% - Modifier inconnu (r)", "%r test d'une phrase");

	printf("Test reussis: %s%d / %d\033[0m\n", test_neg == 0 ? "\033[32m" : "\033[31m", test_pos, test_pos + test_neg);

	return(0);
}
