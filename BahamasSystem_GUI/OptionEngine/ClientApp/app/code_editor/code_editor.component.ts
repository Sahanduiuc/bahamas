import { Component, OnInit } from '@angular/core';

@Component({
    selector: "code_editor",
    templateUrl: "./code_editor.component.html",
    styleUrls: ['code_editor.component.css']
})
export class CodeEditor implements OnInit {

    public codeSample: string = `
    static int Main(string[] args) {
        return 0;
    }
`;

    constructor() {

    }

    ngOnInit(): void {
        //var editor = ace.edit("editor");
        //editor.setTheme("ace/theme/monokai");
        //editor.getSession().setMode("ace/mode/csharp");
        //editor.setValue(this.codeSample);
    }
}