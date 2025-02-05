using UnityEngine;

namespace WeDo2Sample
{
    public class Singleton<T> : MonoBehaviour where T : Component
    {
        static T m_instance;

        public static T Instance
        {
            get => m_instance ?? Initialize();
        }

        /// <summary>
        /// �C���X�^���X���쐬����.
        /// </summary>
        /// <returns>�쐬���ꂽ�C���X�^���X.</returns>
        static T Initialize()
        {
            m_instance = FindAnyObjectByType<T>();
            if (m_instance == null)
            {
                var obj = new GameObject(typeof(T).Name);
                m_instance = obj.AddComponent<T>();
            }
            return m_instance;
        }

        protected virtual void Awake()
        {
            if (m_instance == null)
            {
                m_instance = this as T;
            }
            else if (m_instance != this)
            {
                Destroy(gameObject);
            }
        }

        /// <summary>
        /// �C���X�^���X��j������.
        /// </summary>
        protected void Dispose()
        {
            m_instance = null;
        }
    }
}
