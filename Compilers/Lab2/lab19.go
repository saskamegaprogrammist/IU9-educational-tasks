package main

import (
	"fmt"
	"go/ast"
	"go/format"
	"go/parser"
	"go/token"
	"os"
	//"strings"
)

func deleteDeclaration(file *ast.File) {
	var newDecl []ast.Decl
	for i:=0; i<len(file.Decls); i++ {
		var flag bool
		if genDecl, ok := file.Decls[i].(*ast.GenDecl); ok  {
			if valSpec, ok := genDecl.Specs[0].(*ast.ValueSpec); ok {
				//fmt.Println( valSpec.Names[0].Name)
					if valSpec.Names[0].Name == "FILE" || valSpec.Names[0].Name == "LINE"  {
						flag = true
					}
			}
		}
		if !flag {
			newDecl = append(newDecl, file.Decls[i]);
		}
	}
	file.Decls = newDecl
	delete(file.Scope.Objects, "FILE")
	delete(file.Scope.Objects, "LINE")
}

func check(exp []ast.Expr) {

}

//func checkOneLine(expr ast.Expr) bool {
//	if id, ok := expr.(*ast.Ident); ok  {
//		if id.Name == "LINE" {
//			fmt.Println(id.NamePos)
//			//id.Name = "13";
//			return true
//		}
//	}
//	return false
//}
//func checkOneFile(expr ast.Expr) bool {
//	if id, ok := expr.(*ast.Ident); ok {
//		if id.Name == "FILE" {
//			return true
//		}
//	}
//	return false
//}

func replaceVars(file *ast.File, set *token.FileSet) {

	ast.Inspect(file, func(node ast.Node) bool {

		if id, ok := node.(*ast.Ident); ok {
			if id.Name == "FILE" {
				id.Name = fmt.Sprintf("\"%s\"", os.Args[1])
			}

			if id.Name == "LINE" {
				id.Name = fmt.Sprintf("\"%d\"", set.Position(id.NamePos).Line)
			}
		}


		return true
	})
}


func main() {
	if len(os.Args) != 2 {
		fmt.Printf("usage: astprint <filename.go>\n")
		return
	}

	// Создаём хранилище данных об исходных файлах
	fset := token.NewFileSet()

	// Вызываем парсер
	if file, err := parser.ParseFile(
		fset,                 // данные об исходниках
		os.Args[1],           // имя файла с исходником программы
		nil,                  // пусть парсер сам загрузит исходник
		parser.ParseComments, // приказываем сохранять комментарии
	); err == nil {
		// Если парсер отработал без ошибок, печатаем дерево
		deleteDeclaration(file)
		replaceVars(file, fset)
		format.Node(os.Stdout, fset, file)
		//ast.Fprint(os.Stdout, fset, file, nil)
	} else {
		// в противном случае, выводим сообщение об ошибке
		fmt.Printf("Error: %v", err)
	}
}
