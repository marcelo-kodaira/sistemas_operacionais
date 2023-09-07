<h1 align="center"> Exercícios Lab02a</h1>

**Nome dos Integrantes do Grupo:**
```
Daniel Eiji Tanaami - 32273223
Marcelo Kodaira - 32274297
Gabriel Leal Leone - 32249659



>Exemplos das execuções realizadas para estes programas se encontram nos arquivos ".txt"

**1) 1 Rode o programa anterior para valores grandes de n. As mensagens sempre estarão ordenadas pelo valor de i?**


Ao rodar o programa anterior utilizando o stderr como streaming de saída, as mensagens sempre estarão ordenadas pelo valor de "i", mesmo para valores grandes de "n". Isso pode ser confirmado executando o programa para n = 10000.


**2) O que acontece se o programa anterior escreve-se as mensagens
para sys.stdout, usando print, ao invés de para sys.stderr?**


Se o programa anterior escrever as mensagens para sys.stdout usando a função print, em vez de sys.stderr, o "i" não ficará totalmente em ordem todas as vezes(i=24 a i=27 do arquivo .txt, por exemplo), especialmente para valores grandes de "n". Isso ocorre porque a stdout é bufferizada, e isso pode causar problemas na hora de imprimir os dados. 
Para evitar esse problema, é possível usar a função fflush() para limpar o buffer e garantir que os dados sejam impressos corretamente.

