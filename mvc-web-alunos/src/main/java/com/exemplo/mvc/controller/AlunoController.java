package com.exemplo.mvc.controller;

import com.exemplo.mvc.model.Aluno;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.ArrayList;
import java.util.List;

@Controller
public class AlunoController {

    private List<Aluno> alunos = new ArrayList<>();

    @GetMapping("/alunos")
    public String formulario() {
        return "alunos-form";
    }

    @PostMapping("/alunos")
    public String cadastrar(
            @RequestParam String nome,
            @RequestParam String matricula,
            Model model
    ) {
        try {
            Aluno aluno = new Aluno(nome, matricula);
            alunos.add(aluno);
            model.addAttribute("alunos", alunos);
            return "alunos-lista";
        } catch (IllegalArgumentException erro) {
            model.addAttribute("mensagemErro", erro.getMessage());
            return "alunos-form";
        }
    }
}
