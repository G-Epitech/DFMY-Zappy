pipeline {
    agent any
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
                        dir('graphic') {
                            sh 'make'
                            sh 'make clean'
                            sh 'make fclean'
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
                        sh 'make tests_run'
                    }
                }
                stage('Graphic') {
                    agent {
                        dockerfile true
                    }
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
