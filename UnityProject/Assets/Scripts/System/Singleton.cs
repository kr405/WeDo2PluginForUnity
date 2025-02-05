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
        /// インスタンスを作成する.
        /// </summary>
        /// <returns>作成されたインスタンス.</returns>
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
        /// インスタンスを破棄する.
        /// </summary>
        protected void Dispose()
        {
            m_instance = null;
        }
    }
}
