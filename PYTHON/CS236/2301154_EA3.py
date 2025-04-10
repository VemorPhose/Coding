import numpy as np
import random

class Particle:
	def __init__(self):
		self.position = np.array([random.uniform(0, 500) for _ in range(3)])
		self.velocity = np.array([random.uniform(0, 500) for _ in range(3)])
		self.best_position = self.position.copy()
		self.best_fitness = float('-inf')

class PSO:
	def __init__(self, n_particles=30, max_iters=100):
		self.n_particles = n_particles
		self.max_iters = max_iters
		self.g = 9.8
		self.particles = [Particle() for _ in range(self.n_particles)]
		self.global_best_position = None
		self.global_best_fitness = float('-inf')
	
	def landing_point(self, vx, vy, vz):
		if vz > 0:
			t = 2 * vz / self.g
		else:
			t = 0
		return vx * t, vy * t, 0
	
	def compute_fitness(self, position):
		vx, vy, vz = position
		x, y, z = self.landing_point(vx, vy, vz)
		dist = np.sqrt((x - 100)**2 + (y - 100)**2 + 0.001)
		return 1 / dist
	
	def update_particle(self, particle):
		w = 0.7
		c1 = c2 = 2
		r1 = random.random()
		r2 = random.random()
		
		cognitive = c1 * r1 * (particle.best_position - particle.position)
		social = c2 * r2 * (self.global_best_position - particle.position)
		particle.velocity = w * particle.velocity + cognitive + social
		particle.velocity = np.clip(particle.velocity, 0, 500)
		particle.position = particle.position + particle.velocity
		particle.position = np.clip(particle.position, 0, 500)

		fitness = self.compute_fitness(particle.position)
		if fitness > particle.best_fitness:
			particle.best_fitness = fitness
			particle.best_position = particle.position.copy()
		if fitness > self.global_best_fitness:
			self.global_best_fitness = fitness
			self.global_best_position = particle.position.copy()

def compute_distance(position):
	x, y, z = position
	return np.sqrt((x - 100)**2 + (y - 100)**2)

def main():
	swarm = PSO()
	for particle in swarm.particles:
		particle.best_fitness = swarm.compute_fitness(particle.position)
		if particle.best_fitness > swarm.global_best_fitness:
			swarm.global_best_fitness = particle.best_fitness
			swarm.global_best_position = particle.best_position.copy()
	for _ in range(swarm.max_iters):
		for particle in swarm.particles:
			swarm.update_particle(particle)
		if compute_distance(swarm.global_best_position) < 0.1:
			break
	print("Best solution found:")
	vx, vy, vz = swarm.global_best_position
	print("vx =", vx, ", vy =", vy, ", vz =", vz)
	print("Distance to target:", compute_distance(swarm.global_best_position), "\n")

if __name__ == '__main__':
	main()