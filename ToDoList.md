# 待完善、bugs #
  * 单个 entity 的旋转、缩放、平移
  * camera 的旋转、缩放、平移
  * World 里 camera 组要以数组保存、
  * camera 里增加成员变量 name
  * entity array 等都加名字，改成 map
  * world 里的 camera 是个对象，需要支持对个，并存指针


# Toy3D 引擎 #
  * FBO  render target
  * 观察者模式在引擎中的应用，如 frame listener, target listerer 等
  * 资源管理   http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Resources+and+ResourceManagers
  * Texture/TextureManager 接口的整理，load unload
  * 支持动画  http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Intermediate+Tutorial+1&structure=Tutorials
  * 显示文字
  * glCompressedTexture
  * 渲染队列
  * terrain paging   http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Terrain&structure=Libraries
  * paging 算法不一定适用于图片管理。大规模场景已经存在，只是漫游问题，大规模图片只是纹理管理，可能模型都不用改变


# 通用数据结构 #

  * map : 红黑树


# 应用、例子 #
  * 地图渲染：FBO， layer, shader based blending
  * imageViewer 放到 examples 里
  * coverflow
  * 游动的鱼




# 未确定 #
  * destroy resource 分散在各个 manager，用户需要逐个 manager 的调 create/destroy 函数
  * 当释放 manager 的某一个资源时，数组中间会空出来
  * ogre 设计了 ResourceGroupManager，将各个 manager 聚拢起来，参考 OGRE/Samples
  * 无法索引、查找资源
  * 每个 manager 调用 destroy 很繁琐
  * 各个 manager 开放给用户还是包到某个类里
  * Resource父类、ResouceManager 父类





# 参考 #

  * ogre
  * min3d: android Java OpenGL ES engine
  * le3d: android Java OpenGL engine
  * KplayGE: C++ engine
  * jmonkey
  * osg