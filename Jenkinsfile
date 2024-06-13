pipeline {
    agent any
    options {
        skipDefaultCheckout(true)
    }
    stages {
        stage('Project compilation') {
            parallel {
                stage('Server') {
                    agent {
                        docker {
                            image 'epitechcontent/epitest-docker'
                        }
                    }
                    steps {
                        cleanWs()
                        checkout scm
                        dir('server') {
                            sh 'make'
                            sh 'make clean'
                            sh 'make fclean'
                        }
                    }
                }
                stage('Graphic') {
                    agent {
                        dockerfile true
                    }
                    steps {
                        cleanWs()
                        checkout scm
                        dir('graphic') {
                            sh 'make'
                            sh 'make clean'
                            sh 'make fclean'
                        }
                    }
                }
            }
        }
        stage('Project linting') {
            parallel {
                stage('Server') {
                    steps {
                        cleanWs()
                        checkout scm
                        dir('server') {
                            sh 'docker run --rm -v "$PWD:/mnt/delivery" ghcr.io/epitech/coding-style-checker:latest /mnt/delivery /mnt/reports'
                        }
                    }
                }
            }
        }
        stage('Project tests') {
            parallel {
                stage('Server') {
                    agent {
                        docker {
                            image 'epitechcontent/epitest-docker'
                        }
                    }
                    steps {
                        cleanWs()
                        checkout scm
                        dir('server') {
                            sh 'make tests_run'
                        }
                    }
                }
                stage('Graphic') {
                    agent {
                        dockerfile true
                    }
                    steps {
                        cleanWs()
                        checkout scm
                        dir('graphic') {
                            sh 'make tests_run'
                        }
                    }
                }
            }
        }
        stage('Global compilation') {
            agent {
                dockerfile true
            }
            steps {
                cleanWs()
                checkout scm
                sh 'make'
                sh 'make clean'
                sh 'make fclean'
            }
        }
    }
    post {
        always {
            deleteDir()
       }
    }
}
