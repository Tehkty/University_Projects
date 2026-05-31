# Projeto MVC Web - Cadastro de Alunos

Este projeto foi desenvolvido como exemplo de aplicação Web utilizando o padrão MVC.

## Tecnologias utilizadas

- Java 17
- Spring Boot
- Spring Web
- Thymeleaf
- Maven
- Visual Studio Code

## Estrutura MVC

```text
src/main/java/com/exemplo/mvc/
├── model/
│   └── Aluno.java
├── controller/
│   └── AlunoController.java
└── MvcApplication.java

src/main/resources/
├── templates/
│   ├── alunos-form.html
│   └── alunos-lista.html
└── application.properties
```

## Model

A classe `Aluno` representa os dados e contém uma regra simples de negócio: o nome e a matrícula não podem ser vazios.

## Controller

A classe `AlunoController` recebe as requisições do navegador, cria os alunos e envia os dados para a View.

## View

As páginas HTML `alunos-form.html` e `alunos-lista.html` são responsáveis apenas pela apresentação das informações.

## Como executar

No terminal, dentro da pasta do projeto, execute:

```bash
mvn spring-boot:run
```

Depois, acesse no navegador:

```text
http://localhost:8080/alunos
```

## Como subir no GitHub

```bash
git init
git add .
git commit -m "Projeto MVC Web - Cadastro de Alunos"
git branch -M main
git remote add origin https://github.com/SEU_USUARIO/mvc-web-alunos.git
git push -u origin main
```
