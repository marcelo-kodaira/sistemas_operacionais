<h1 align="center"> Projeto 01 </h1>


> Contas bancarias.



**Nome dos Integrantes do Grupo:**

```
Gabriel Leal Leone 32249659
Daniel Eiji Tanaami 32273223
Marcelo Kodaira de Almeida 32274297
```

**Como compilar o programa:**

```
Utilizando o GCC, devemos utilizar o comando no terminal : gcc main.c -o main.out

```

**Reqisitos do projeto:**

**1. A conta to pode receber mais de uma transferência simultânea**

**2. A conta from pode enviar mais de uma transferência simultânea**

Resolvido com a utilização de threads no código , ao chamar a rotina que possui transferências para ambas as contas.
![242298960-599732bb-b7c3-4d27-92bc-2a7b8ebbb742](https://github.com/marcelo-kodaira/sistemas_operacionais/assets/112910311/e103ccfe-914e-475f-8829-628335b96dcf)


**3. A conta from não pode enviar dinheiro se não tiver mais saldo**

A conta só transfere enquanto possui dinheiro

![242300186-658c313a-c800-4847-96a8-e0b3220da925](https://github.com/marcelo-kodaira/sistemas_operacionais/assets/112910311/8dbe6506-6c8f-4e61-a1c4-fef65c55420b)



**4. A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode**
receber e a conta que recebia pode enviar;

Com as flags ambas as contas podem enviar e receber , onde caso uma deles zere a outra passa a transferir e vice-versa.

![242300535-294649f1-9dd7-4e2c-a5b0-827f689f965b](https://github.com/marcelo-kodaira/sistemas_operacionais/assets/112910311/8d6aeaf4-a2ee-4ec3-8d68-8adb124ed899)



**5. Poderão ser realizadas até 100 transações simultâneas de transferência.**

São utilizadas 100 threads e no loop a rotina é chamada de 0 a 100 vezes.

![242301576-6733e953-aa67-4359-a224-d4923f4ad140](https://github.com/marcelo-kodaira/sistemas_operacionais/assets/112910311/1ff54326-f402-48e0-b352-ba3a4d27f6a4)

![242301681-1796ff64-8a81-443c-91ba-376468b4d81a](https://github.com/marcelo-kodaira/sistemas_operacionais/assets/112910311/a7e03207-e977-4ccb-86e8-3b8529f4b97a)

Também é utilizado uma mutex no código , garantindo a integridade e o funcionamento adequado das threads.

