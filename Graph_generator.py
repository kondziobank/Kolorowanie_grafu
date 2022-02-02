import random
class graph_generator:
    def __init__(self,number_of_vertices, number_of_edges):
        self.edges=[]
        self.number_of_vertices=number_of_vertices
        self.number_of_edges=number_of_edges
        self.make_edges()
    def make_edges(self):
        self.edges.append([1,2])
        count_edges=0
        for i in range(3,self.number_of_vertices+1):
            v=random.randint(1,i-1)
            self.edges.append([v,i])
            count_edges+=1
        while count_edges<=self.number_of_edges:
            v1=random.randint(1,self.number_of_vertices)
            v2=random.randint(1,self.number_of_vertices)
            while v1==v2:
                v1=random.randint(1,self.number_of_vertices)
                v2=random.randint(1,self.number_of_vertices)
            v1,v2=sorted([v1,v2])
            if not( [v1,v2] in self.edges):
                self.edges.append([v1,v2])
                count_edges+=1
            else:
                continue
        self.edges.sort()
    def print_graph(self):
        print(self.number_of_vertices)
        for i in self.edges:
            print(i[0], " ", i[1])
    def write_graph_to_file(self,fileName):
        f=open(f"{fileName}", "w+")
        f.write(str(str(self.number_of_vertices)+"\n"))
        for i in self.edges:
            f.write(str(str(i[0])+" "+str(i[1])+"\n"))

        

if __name__=="__main__":
    for i in range(10):
        graf=graph_generator(20,100)
        s="test"+str(i)
        graf.write_graph_to_file(s)


        
