FROM epitechcontent/epitest-docker:latest

RUN yum install \
        bullet-devel \
        zziplib-devel \
        freetype-devel \
        freeimage-devel \
        -y

WORKDIR /tmp
RUN wget -qO- https://github.com/OGRECave/ogre/archive/refs/tags/v14.2.6.tar.gz | tar xvz
RUN mkdir /tmp/ogre-14.2.6/build
WORKDIR /tmp/ogre-14.2.6/build
RUN cmake ..
RUN make
RUN sudo make install
RUN ln -s /usr/include/bullet /usr/local/include/bullet
RUN rm -rf /tmp/ogre-14.2.6

WORKDIR /usr/app
