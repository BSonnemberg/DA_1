# IMPORTANT ELEMENTS
[Full Project 1 Description](https://moodle2324.up.pt/pluginfile.php/233126/mod_resource/content/1/Project1Description-rev1.pdf)
### Water Reservoir (WR)
Graph nodes that provide water to the entire network. Maximum capacity of < X m^3/sec. Connected to Pumping Stations (PS) by pipelines of maximum capacity of Y m^3/sec.
### Pumping Stations (PS)
Graph nodes that direct or redirect water flow from other PS or WR to the costumers or DS.
### Delivery Sites (DS)
Graph nodes directly connect the water supply to the costumer. It has a specific rate demand of Z m^3/sec.

# MANDATORY FEATURES

### Read and Parse Input Data: 
Load and parse the provided dataset files to extract information about the water supply network.
### Determine Maximum Water Flow: 
Determine the maximum amount of water that can reach each or a specific city using the Edmonds-Karp maximum-flow algorithm.
### Check Network Configuration: 
Verify if the existing network configuration can meet the water needs of all delivery sites.
### Balance Load Across Network: 
Develop an algorithm to balance the load across the network, minimizing differences of flow to capacity on each pipe.
### Evaluate Resiliency: 
Evaluate the network's resiliency by simulating the impact of removing specific water reservoirs.
### Temporary Pumping Station Removal: 
Determine if any pumping station can be temporarily taken out of service without affecting water delivery to all cities.
### Pipeline Failure Analysis: 
Identify potential pipeline failures and their impact on water supply to each city.

## Basic Service Metrics (Notes)
### Determine Maximum Water Flow: 
Implement the Edmonds-Karp algorithm to find the optimal flow through the network.
### Check Network Configuration: 
Sum up water capacity being delivered to each site to verify if all water needs are met.
### Balance Load Across Network: 
Develop an algorithm to minimize differences of flow to capacity on each pipe.

___________________________________________________________

Project developed by
* Beatriz Sonnemberg
* Gonçalo Sousa
* Nuno Rios