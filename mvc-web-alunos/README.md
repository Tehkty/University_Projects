# Projeto MVC Web - Cadastro de Alunos

## Objetivo

Este projeto demonstra a aplicação do padrão arquitetural MVC (Model-View-Controller) em uma aplicação Web desenvolvida com Spring Boot e Thymeleaf.
O sistema permite cadastrar alunos através de um formulário Web e exibir os alunos cadastrados.

---

## Como o padrão MVC foi aplicado

### Model

Classe: `Aluno.java`

Responsável por representar os dados do aluno e suas regras de negócio.

A classe possui os atributos:

* nome
* matricula

Também realiza validações, como impedir a criação de um aluno sem nome.

O Model não possui conhecimento sobre:

* páginas HTML;
* requisições HTTP;
* navegador;
* Spring MVC.

Sua única responsabilidade é representar e validar os dados da aplicação.

---

### View

Arquivos:

* `alunos-form.html`
* `alunos-lista.html`

Responsáveis pela interface apresentada ao usuário.

Funções da View:

* exibir o formulário de cadastro;
* mostrar a lista de alunos cadastrados;
* receber os dados digitados pelo usuário.

A View não contém regras de negócio nem controla o fluxo da aplicação.

---

### Controller

Classe: `AlunoController.java`

Responsável por intermediar a comunicação entre View e Model.

Funções do Controller:

1. Receber as requisições HTTP;
2. Capturar os dados enviados pelo formulário;
3. Criar objetos do Model;
4. Enviar os dados para a View;
5. Definir qual página será exibida.

O Controller coordena o funcionamento da aplicação, mas não implementa regras de negócio nem gera HTML diretamente.

---

## Fluxo da Aplicação

1. O usuário acessa a rota `/alunos`;
2. O Controller retorna a View `alunos-form.html`;
3. O usuário preenche o formulário;
4. O formulário envia os dados para o Controller;
5. O Controller cria um objeto `Aluno`;
6. O objeto é armazenado na lista de alunos;
7. O Controller envia a lista para a View;
8. A View `alunos-lista.html` apresenta os dados ao usuário.

---

## Estrutura MVC do Projeto

```text
src
├── main
│   ├── java
│   │   └── com.exemplo.mvc
│   │       ├── model
│   │       │   └── Aluno.java
│   │       ├── controller
│   │       │   └── AlunoController.java
│   │       └── MvcApplication.java
│   │
│   └── resources
│       ├── templates
│       │   ├── alunos-form.html
│       │   └── alunos-lista.html
│       └── application.properties
│
└── pom.xml
```

---

## Justificativa da Separação de Responsabilidades

O padrão MVC foi utilizado para separar claramente as responsabilidades da aplicação.

O Model concentra os dados e regras de negócio, mantendo independência em relação à interface gráfica e ao protocolo HTTP.

A View é responsável apenas pela apresentação das informações ao usuário.

O Controller atua como intermediário entre o usuário e o sistema, coordenando as operações e encaminhando os dados entre Model e View.

Essa separação reduz o acoplamento entre as camadas, facilita a manutenção do código e permite a evolução do sistema de forma organizada.

---

## Tecnologias Utilizadas

* Java 21
* Spring Boot
* Spring Web
* Thymeleaf
* Maven
* Visual Studio Code

---

## Como Executar

### Pré-requisitos

* Java JDK 21 ou superior
* Maven
* Visual Studio Code
* Extension Pack for Java
* Spring Boot Extension Pack

### Executando pelo VS Code

1. Abrir a pasta do projeto;
2. Aguardar a importação do Maven;
3. Abrir a classe `MvcApplication.java`;
4. Clicar em **Run**.

### Executando pelo terminal

```bash
mvn spring-boot:run
```

---

## Testando a Aplicação

Após iniciar o projeto, acessar:

```text
http://localhost:8080/alunos
```

Será exibido o formulário de cadastro de alunos.

---

## Conclusão

O projeto demonstra a aplicação prática do padrão MVC em aplicações Web utilizando Spring Boot.

A separação entre Model, View e Controller permite melhor organização do código, maior reutilização de componentes e facilita a manutenção e evolução do sistema.
