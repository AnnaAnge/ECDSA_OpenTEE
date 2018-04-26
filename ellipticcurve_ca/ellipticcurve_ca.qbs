import qbs

CppApplication {
    type: "application"
    name: "ellipticcurve_ca"
    Group {
        name: "project-install"
        fileTagsFilter: "application"
        qbs.install: false
        qbs.installDir: "bin"
    }

    Depends { name: "tee" }
    consoleApplication: true
    destinationDirectory: '.'

    files: [
        
        'ellipticcurve_ca.c'
    ]
}
