import numpy as np
class MLP(object):
    def __init__(self, num_inputs=3, hidden_layers=[3, 3], num_outputs=2):
        self.num_inputs = num_inputs
        self.hidden_layers = hidden_layers
        self.num_outputs = num_outputs

        layers = [num_inputs] + hidden_layers + [num_outputs]

        weights = []
        for i in range(len(layers)-1):
            w = np.random.rand(layers[i], layers[i+1])
            weights.append(w)
        self.weights = weights

        activations = []
        for i in range(len(layers)):
            a = np.zeros(layers[i])
            activations.append(a)
        self.activations = activations

        derivatives = []
        for i in range(len(layers)-1):
            d = np.zeros(layers[i], layers[i+1])
            derivatives.append(d)
        self.derivatives = derivatives


    def forward_propagate(self, inputs):
        activations = inputs
        self.activations[0] = inputs
        for i, w in enumerate(self.weights):
            net_inputs = np.dot(activations, w)
            activations = self._sigmoid(net_inputs)
            self.activations[i+1] = activations
        return activations
    def back_propagate(self, error, verbose=False):
        for i in reversed(range(len(self.derivatives))):
            activations = self.activations[i+1]
            delta = error * self._sigmoid_derivative(activations)
            delta_reshaped = delta.reshape(delta.shape[0], -1).t
            current_activations = self.activations[i]
            current_activations_reshaped = current_activations.reshape(current_activations.shape[0], -1)
            self.derivatives[i] = np.dot(current_activations, delta_reshaped)
            error = np.dot(delta, self.weights[i].t)
            
            if verbose:
                print('derivatives for w{}: {}'.format(i, self.derivatives[i]))
        return error
    def _sigmoid_derivative(self, x):
        return x * (1.0 - x)


    def _sigmoid(self, x):
        return 1.0 / (1 + np.exp(-x))

if __name__ == "__main__":
    mlp = MLP(2, [5], 1)
    input = np.array([0.1, 0.2])
    target = np.array([0.3])
    output = mlp.forward_propagate(input)

    error = target - output
    mlp.back_propagate(error, verbose=True)