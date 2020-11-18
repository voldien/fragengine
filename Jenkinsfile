pipeline {
	agent {
		docker {
			image 'lycantropos/cmake:3.9.5'
		}
	}

	stages {
		stage('Build') {
			steps {
				echo 'Building..'
				cmakeBuild  installation: "InSearchPath",
											generator: "Unix Makefile",
											buildDir: 'build',
											sourceDir: 'source',
											steps: [
												[args: 'all install']
											]
			}
		}
		stage('Test') {
			steps {
				echo 'Testing..'
				ctest 'InSearchPath'
			}
		}
		stage('Deploy') {
			steps {
				echo 'Deploying....'
			}
		}
	}
}