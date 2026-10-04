# Diário da atividade

Escreva com as suas palavras. Frases curtas bastam. Não cole a conversa inteira
com a IA. Cole só os pedidos que você enviou.

## Ambiente

- Versão do OpenCode (`opencode --version`):
- Modelo usado:

## Parte 1: antes de programar

- O que cada classe guarda:
- O que acontece em `LANCAR_VOO`, em palavras:
- Uma dúvida que eu tinha antes de começar:

## Parte 1: uso de IA para entender algo

- O que perguntei (ou "não usei"):
- O que aprendi:

## Primeiro contato: revisão sem editar

- As três melhorias que a IA sugeriu, em uma linha cada:
- A que escolhi e por quê:
- O que mudou no código, e se os seis testes continuaram passando:
- O que entendi que não sabia antes:

## Missão 1: LISTAR_ASTRONAUTAS e HISTORICO

• Primeira mensagem (o pedido do plano):
Pedi para implementar os comandos LISTAR_ASTRONAUTAS e HISTORICO, seguindo as regras do enunciado e sem alterar os comandos existentes. Pedi primeiro apenas o plano, sem editar os arquivos.

• O plano que a IA apresentou, resumido:
A IA planejou alterar agencia.h, agencia.cpp e main.cpp. Criaria métodos para listar os astronautas por situação e mostrar o histórico de voos, além de adicionar os novos comandos no main.cpp.

• Mudei algo no plano antes de liberar?
Não mudei o plano antes de liberar.

• Resultado de testar.sh missao1 e de testar.sh parte1:
missao1: 2 de 2 testes passaram.
parte1: 6 de 6 testes passaram.

• Precisei refazer? O que mudou no pedido:
Sim. Depois da primeira implementação percebi que o HISTORICO usava ponteiro, o que era proibido pelas regras. Pedi para refazer essa parte sem ponteiros. Depois disso, todos os testes continuaram passando.

## Missão 2: SALVAR e CARREGAR

- Pedi à IA para implementar os comandos SALVAR e CARREGAR, explicando o que cada um deveria fazer.
- Analisei o plano e pedi esclarecimentos sobre a disponibilidade dos astronautas e a preservação dos dados em caso de erro.
- A IA implementou os comandos e explicou como o carregamento valida os dados antes de substituir os atuais.
- Testes da Missão 2: 3 de 3 passaram.
- Testes da Parte 1: 6 de 6 passaram.
- Testes da Missão 1: 2 de 2 passaram.

## Missão 3: RELATORIO

- Primeira mensagem: Pedi à IA para planejar a implementação do comando RELATORIO sem alterar arquivos.
- O plano, resumido: Contar os voos por estado, os astronautas cadastrados, vivos e mortos, identificar o astronauta mais experiente e calcular a taxa de sucesso.
- Mudei algo no plano antes de liberar? Pedi esclarecimentos sobre o cálculo da experiência, a identificação do astronauta mais experiente e a ordem e o texto exatos das linhas do relatório.
- Resultado de testar.sh missao3 e de testar.sh parte1: Missão 3: 5 de 5 testes passaram. Parte 1: 6 de 6 testes passaram.
- Precisei refazer? Não. Pedi esclarecimentos antes de autorizar a implementação, e a versão implementada passou em todos os testes.

## Missão 4: livre


- O que escolhi e por quê: escolhi o comando DEMO para carregar um cenário de demonstração sem precisar digitar todos os comandos manualmente.
- O comando novo, a saída que eu esperava e o nome do meu arquivo de comandos: escolhi o comando DEMO, que deveria carregar dois astronautas e dois voos, sendo um finalizado com sucesso e outro com explosão. Criei o arquivo meu_demo.txt para conferir o resultado usando DEMO, LISTAR_VOOS, LISTAR_MORTOS e RELATORIO.
- Primeira mensagem: pedi primeiro um plano de implementação, sem permitir alterações nos arquivos.
- O que veio, comparado com o que eu esperava: o cenário foi carregado corretamente. Quando executei DEMO novamente, o sistema recusou a operação e não duplicou os cadastros.
- Os testes: os 6 testes da Parte 1 passaram, assim como os 5 testes da Missão 3. Também executei meu_demo.txt para conferir o cenário da Missão 4.
- Aceitei, ajustei ou descartei? Aceitei a implementação depois de revisar o plano e conferir os resultados.

## Fechamento

-## Fechamento

- O que a IA fez que eu não conseguiria fazer sozinho nesse prazo: ajudou a implementar novas funcionalidades, organizar o código e verificar o funcionamento por meio dos testes.
- Onde ela errou ou fez algo que eu não pedi: durante a Missão 1, a primeira implementação do HISTORICO utilizou ponteiros, o que não era permitido pelas regras. Pedi uma correção sem ponteiros e os testes passaram. Na Missão 4, revisei o plano antes de autorizar a implementação.
- O que eu faria diferente da próxima vez: definiria os cenários de teste antes de implementar cada funcionalidade e revisaria o plano com atenção antes de autorizar as alterações.