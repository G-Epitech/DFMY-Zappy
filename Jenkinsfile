pipeline {
    agent any
    stages {
        stage('Server') {
            stages {
                stage('Project compilation') {
                    agent {
                        image 'epitechcontent/epitest-docker'
                    }
                    steps {
                        sh 'make'
                        sh 'make clean'
                        sh 'make fclean'
                    }
                }
                stage('Project linting') {
                    agent {
                        image 'ghcr.io/epitech/coding-style-checker:latest'
                    }
                    steps {
                        sh 'check.sh $(pwd) $(pwd)'
                    }
                }
                stage('Project tests') {
                    agent {
                        image 'epitechcontent/epitest-docker'
                    }
                    steps {
                        sh 'make tests_run'
                    }
                }
            }
        }

        stage('Graphic') {
            agent {
                dockerfile true
            }
            stages {
                stage('Project compilation') {
                    steps {
                        sh 'make'
                        sh 'make clean'
                        sh 'make fclean'
                    }
                }
                stage('Project tests') {
                    steps {
                        sh 'make tests_run'
                    }
                }
            }
        }

        stage('Global compilation') {
            agent {
                dockerfile true
            }
            steps {
                sh 'make'
                sh 'make clean'
                sh 'make fclean'
            }
        }
    }
}
