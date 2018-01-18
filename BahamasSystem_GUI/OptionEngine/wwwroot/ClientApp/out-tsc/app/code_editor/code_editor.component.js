var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
import { Component } from '@angular/core';
let CodeEditor = class CodeEditor {
    constructor() {
        this.codeSample = `
    static int Main(string[] args) {
        return 0;
    }
`;
    }
    ngOnInit() {
        //var editor = ace.edit("editor");
        //editor.setTheme("ace/theme/monokai");
        //editor.getSession().setMode("ace/mode/csharp");
        //editor.setValue(this.codeSample);
    }
};
CodeEditor = __decorate([
    Component({
        selector: "code_editor",
        templateUrl: "./code_editor.component.html",
        styleUrls: ['code_editor.component.css']
    }),
    __metadata("design:paramtypes", [])
], CodeEditor);
export { CodeEditor };
//# sourceMappingURL=code_editor.component.js.map